import pynvim
import glob

@pynvim.plugin
class NextFile(object):

    def __init__(self, nvim):
        self.nvim = nvim
        self.delete_len = 0
        self.latest_file = None
        self.file_list = []

    @pynvim.command('NextFile', nargs='?', range='', sync = True)
    def next_file(self, args, range):
        if len(args) != 0 :
            try :
                self.delete_len = int(args[0])
            except:
                self.delete_len = 0

        curr_filename = self.nvim.eval("expand('%')")
        next_filename = self._next_filename(curr_filename)
        self.nvim.command(f"edit {next_filename}")

    def _next_filename(self, filename) :

        if self.delete_len == 0 :
            body, *_ = filename.split(".")
        else:
            body = filename[0 : len(filename) - self.delete_len]
            self.latest_file = None

        if self.latest_file != filename :
            self.file_list = glob.glob(body + "*")

        for i, f in enumerate(self.file_list) :
            if filename == f :
                self.latest_file = self.file_list[(i + 1) % len(self.file_list)]

                return self.latest_file

