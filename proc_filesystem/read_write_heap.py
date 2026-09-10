#!/usr/bin/python3
"""Find and replace a string in the heap of a running process."""

import sys


def get_heap(pid):
    """Return the start and end addresses of the process heap."""
    maps_path = "/proc/{}/maps".format(pid)

    with open(maps_path, "r") as maps:
        for line in maps:
            if "[heap]" in line:
                addresses = line.split()[0].split("-")
                return int(addresses[0], 16), int(addresses[1], 16)

    return None, None


def replace_in_heap(pid, search, replace):
    """Find and replace a string in the process heap."""
    start, end = get_heap(pid)

    if start is None:
        return False

    search_bytes = search.encode("ascii")
    replace_bytes = replace.encode("ascii")

    if len(replace_bytes) > len(search_bytes):
        return False

    mem_path = "/proc/{}/mem".format(pid)

    with open(mem_path, "r+b", buffering=0) as mem:
        mem.seek(start)
        heap = mem.read(end - start)

        position = heap.find(search_bytes)

        if position == -1:
            return False

        new_value = replace_bytes
        new_value += b"\0" * (len(search_bytes) - len(replace_bytes))

        mem.seek(start + position)
        mem.write(new_value)

    return True


def main():
    """Run the program."""
    if len(sys.argv) != 4:
        print("Usage: read_write_heap.py pid search_string replace_string")
        sys.exit(1)

    pid = sys.argv[1]
    search = sys.argv[2]
    replace = sys.argv[3]

    try:
        int(pid)
        search.encode("ascii")
        replace.encode("ascii")
    except ValueError:
        print("Error: invalid PID")
        sys.exit(1)
    except UnicodeEncodeError:
        print("Error: strings must be ASCII")
        sys.exit(1)

    try:
        replace_in_heap(pid, search, replace)
    except (FileNotFoundError, PermissionError, OSError):
        print("Error: unable to access process")
        sys.exit(1)


if __name__ == "__main__":
    main()
