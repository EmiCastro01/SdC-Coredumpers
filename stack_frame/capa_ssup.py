from msl.loadlib import Server32

import ctypes


class MiServer(Server32):
    def __init__(self, host, port, **kwargs):
        super(MiServer, self).__init__("capa_med.so", "cdll", host, port)
        self.lib.get_gini.argtypes = [ctypes.c_float]
        self.lib.get_gini.restype = ctypes.c_int

    def get_gini(self, gini_valor):
        return self.lib.get_gini(gini_valor)
