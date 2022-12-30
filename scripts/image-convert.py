from pathlib import Path
from sys import argv

from PIL import Image


def main(image_path):
    src = Path(image_path).absolute()

    img = Image.open(src).convert('RGBA')
    width, height = img.size

    is_alpha = False
    for y in range(height):
        for x in range(width):
            is_alpha = is_alpha or img.getpixel((x, y))[3] != 0xff

    with open(src.with_suffix('.h'), 'w') as out:
        out.write(f'const uint8_t IMAGE_{src.stem.upper()}[] PROGMEM = {{  //\n')
        out.write(f'{width}, {height}')

        for x in range(width):
            for y in range(0, height, 8):
                a = b = 0

                for p in range(8):
                    if y + p == height:
                        break

                    pixel = img.getpixel((x, y + p))

                    if sum(pixel) - pixel[3] not in (0xff * 3, 0x00):
                        print(f'Warning: pixel at ({x}, {y + p}) is coloured')

                    if pixel[3] not in (0xff, 0x00):
                        print(f'Warning: pixel at ({x}, {y + p} has float transparency')

                    a |= (pixel[3] == 0xff) << p
                    b |= (sum(pixel) - pixel[3] == 0xff * 3) << p

                out.write(f', 0x{b:02x}')
                if is_alpha:
                    out.write(f', 0x{a:02x}')

        out.write('};\n')


if __name__ == '__main__':
    for i in range(1, len(argv)):
        arg = argv[i]
        print(f'Processing {arg}')
        main(arg)
