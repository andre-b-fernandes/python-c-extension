from distutils.core import setup, Extension
import os

os.environ['CFLAGS'] = '-mavx'
#os.environ["CC"] = "g++"


module1 = Extension(
    'matmul',
    define_macros = [('MAJOR_VERSION', '1'),
                     ('MINOR_VERSION', '0')],
    include_dirs = ['/usr/local/include'],
    library_dirs = ['/usr/local/lib'],
    sources = ['matmul.c'],
    extra_compile_args=["-mavx", "-O3"]
)

setup (name = 'matmul',
       version = '1.0',
       description = 'This is a demo package',
       author = 'Andre Fernandes',
       author_email = 'fernandoandre49@gmail.com',
       url = 'https://docs.python.org/extending/building',
       long_description = '''
            This is really just a demo package.
        ''',
       ext_modules = [module1],
)

