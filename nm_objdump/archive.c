#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hnm.h"

#define AR_MAGIC "!<arch>\n"
#define AR_HDR_SIZE 60

/**
 * is_archive - check if a buffer holds an ar archive
 * @data: file contents
 * @size: size of the contents
 *
 * Return: 1 if it is an archive, 0 otherwise
 */
int is_archive(const unsigned char *data, size_t size)
{
	return (size >= 8 && !memcmp(data, AR_MAGIC, 8));
}

/**
 * member_name - extract the name of an archive member
 * @hdr: member header
 * @lnames: GNU long names table (or NULL)
 * @lsize: size of the long names table
 * @buf: buffer of at least 256 bytes receiving the name
 *
 * Return: buf
 */
static char *member_name(const unsigned char *hdr, const unsigned char *lnames,
			 size_t lsize, char *buf)
{
	size_t i = 0, off;

	if (hdr[0] == '/' && hdr[1] >= '0' && hdr[1] <= '9' && lnames)
	{
		off = strtoul((const char *)hdr + 1, NULL, 10);
		while (off + i < lsize && i < 255 && lnames[off + i] != '/' &&
		       lnames[off + i] != '\n')
		{
			buf[i] = lnames[off + i];
			i++;
		}
	}
	else
	{
		while (i < 16 && hdr[i] != '/' && hdr[i] != ' ')
		{
			buf[i] = hdr[i];
			i++;
		}
	}
	buf[i] = '\0';
	return (buf);
}

/**
 * member_data - locate the data of a member, handling BSD "#1/" names
 * @hdr: member header
 * @size: in: size from the header, out: size of the data
 * @name: buffer of at least 256 bytes, filled for BSD long names
 *
 * Return: offset of the data from the end of the header
 */
static size_t member_data(const unsigned char *hdr, size_t *size, char *name)
{
	size_t len;

	if (memcmp(hdr, "#1/", 3))
		return (0);
	len = strtoul((const char *)hdr + 3, NULL, 10);
	if (len > *size || len > 255)
		len = *size < 255 ? *size : 255;
	memcpy(name, hdr + AR_HDR_SIZE, len);
	name[len] = '\0';
	*size -= len;
	return (len);
}

/**
 * process_archive - list the symbols of every member of an archive
 * @prog: program name
 * @data: archive contents
 * @size: size of the archive
 *
 * Return: 0 on success, 1 on error
 */
int process_archive(const char *prog, const unsigned char *data, size_t size)
{
	size_t off = 8, msize, skip;
	const unsigned char *lnames = NULL;
	size_t lsize = 0;
	char name[256];
	int ret = 0;

	while (off + AR_HDR_SIZE <= size)
	{
		msize = strtoul((const char *)data + off + 48, NULL, 10);
		if (msize > size - off - AR_HDR_SIZE)
			msize = size - off - AR_HDR_SIZE;
		if (!memcmp(data + off, "// ", 3))
		{
			lnames = data + off + AR_HDR_SIZE;
			lsize = msize;
		}
		else if (memcmp(data + off, "/ ", 2) &&
			 memcmp(data + off, "/SYM64/ ", 8))
		{
			member_name(data + off, lnames, lsize, name);
			skip = member_data(data + off, &msize, name);
			if (strcmp(name, "__.SYMDEF") && strcmp(name, "__.SYMDEF SORTED"))
				ret |= process_elf(prog, name,
						   data + off + AR_HDR_SIZE + skip,
						   msize, 2);
			msize += skip;
		}
		off += AR_HDR_SIZE + msize + (msize & 1);
	}
	return (ret);
}
