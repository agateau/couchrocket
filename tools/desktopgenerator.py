import os

from collections import namedtuple
from urllib.request import urlopen

from slugify import slugify


DESKTOP_TEMPLATE = """[Desktop Entry]
Version=1.0
Name={title}
Exec={command} {rom}
Icon={snap}
"""


Config = namedtuple('Config', ['command', 'snap_dir', 'desktop_dir'])


class App:
    EXTENSION = '.notset'

    def __init__(self, config):
        self.config = config

    def process_dir(self, dirname):
        for filename in os.listdir(dirname):
            if filename.endswith(EXTENSION):
                print('Processing {}'.format(filename))
                self.process_file(os.path.join(dirname, filename))

    def process_file(self, filename):
        rom = os.path.basename(os.path.splitext(filename)[0])
        if not self.is_rom(rom):
            print('Unknown, skipping')
        self.download_snap(rom)
        self.create_desktop(rom)

    def is_rom(self, rom):
        """Must return True if rom is a valid rom"""
        return True

    def get_title(self, rom):
        """Must return a title for the rom"""
        raise NotImplementedError()

    def get_snap_url(self, rom):
        """Must return an url for the rom"""
        raise NotImplementedError()

    def do_download_snap(self, rom, snap_path):
        url = self.get_snap_url(rom)

        print('Downloading snap from {}'.format(url))
        with urlopen(url) as srcf:
            with open(snap_path, 'wb') as dstf:
                dstf.write(srcf.read())

    def get_snap_path(self, rom):
        return os.path.join(self.config.snap_dir, rom + '.png')

    def download_snap(self, rom):
        snap_path = self.get_snap_path(rom)
        if os.path.exists(snap_path):
            print('Snap has already been downloaded')
            return

        self.do_download_snap(rom, snap_path)

    def create_desktop(self, rom):
        title = self.get_title(rom)

        desktop_path = os.path.join(self.config.desktop_dir, slugify(title) + '.desktop')
        if os.path.exists(desktop_path):
            print('Desktop file has already been generated')
            return

        snap_path = self.get_snap_path(rom)
        print('Generating {}'.format(desktop_path))
        dct = {
            'command': self.config.command,
            'title': title,
            'rom': rom,
            'snap': snap_path
        }
        with open(desktop_path, 'w') as f:
            f.write(DESKTOP_TEMPLATE.format(**dct))
