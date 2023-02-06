from pathlib import Path
from sys import argv

byte_map = {
    0x00: 0x00,
    0x01: 0x01,
    0x20: 0x02
}


def convert(data):
    width, height = data[6:8]

    # Copy metadata
    res = data[:8]

    # Convert level objects
    res += bytes(byte_map.get(i, 0) for i in data[8:8 + width * height])

    # Copy spider objects
    # res += data[8 + width * height:]

    return res


def compress(data):
    width, height = data[6:8]

    # Metadata isn't compressed
    res = data[:8]

    # Copmress level objects
    prev_byte = b'\x00'
    byte_cnt = 0

    for byte in data[8:8 + width * height]:
        byte = bytes([byte])

        if byte == prev_byte and byte_cnt < 255:
            byte_cnt += 1
        else:
            if byte_cnt > 3:
                res += prev_byte + b'\xff' + bytes([byte_cnt])
            else:
                res += prev_byte * byte_cnt

            byte_cnt = 1

        prev_byte = byte

    if byte_cnt > 3:
        res += prev_byte + b'\xff' + bytes([byte_cnt])
    else:
        res += prev_byte * byte_cnt

    # Spider objects aren't compressed
    # res += data[8 + width * height:]

    return res


def process(src, out):
    with open(src, 'rb') as file:
        data = compress(convert(file.read()))

    out.write(f'const uint8_t LEVEL_{src.stem}[] PROGMEM = {{  //\n')
    out.write(', '.join(f'0x{i:02x}' for i in data))
    out.write('};\n')


def main():
    levels = set()

    with open(argv[1], 'w') as out:
        out.write(
            '#pragma once\n'
            '\n'
            '#include <Arduboy2Ex.h>\n'
            '\n'
        )

        for src in map(Path, argv[2:]):
            print(f'Processing {src}')
            process(src, out)
            levels.add(int(src.stem))
            out.write('\n')

        out.write('const uint8_t* const LEVELS[] = { //\n')
        out.write(', '.join(f'LEVEL_{i}' for i in levels))
        out.write('};\n')


if __name__ == '__main__':
    main()
