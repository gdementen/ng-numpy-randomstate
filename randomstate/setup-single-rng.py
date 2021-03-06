import os
import sys
from distutils.core import setup
from distutils.extension import Extension
from os import getcwd, name
from os.path import join

import numpy
from Cython.Build import cythonize

rngs = ['RNG_PCG32', 'RNG_PCG64',
        'RNG_MT19937', 'RNG_XORSHIFT128',
        'RNG_XORSHIFT1024', 'RNG_MRG32K3A', 'RNG_MLFG_1279_861']

with open('config.pxi', 'w') as config:
    config.write('# Autogenerated\n\n')
    config.write("DEF RS_RNG_MOD_NAME='xorshift128'\n")

pwd = getcwd()

sources = [join(pwd, 'randomstate.pyx'),
           join(pwd, 'src', 'common', 'entropy.c'),
           join(pwd, 'distributions.c')]

sources += [join(pwd, 'src', 'xorshift128', p) for p in ('xorshift128.c',)]
sources += [join(pwd, 'interface', 'xorshift128', 'xorshift128-shim.c')]

defs = [('XORSHIFT128_RNG', '1')]

include_dirs = [pwd] + [numpy.get_include()]
if os.name == 'nt' and sys.version_info < (3, 5):
    include_dirs += [join(pwd, 'src', 'common')]
include_dirs += [join(pwd, 'src', 'xorshift128')]

extra_link_args = ['Advapi32.lib'] if name == 'nt' else []
extra_compile_args = [] if name == 'nt' else ['-std=c99']

setup(ext_modules=cythonize([Extension("core_rng",
                                       sources=sources,
                                       include_dirs=include_dirs,
                                       define_macros=defs,
                                       extra_compile_args=extra_compile_args,
                                       extra_link_args=extra_link_args)
                             ])
      )
