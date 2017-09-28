from distutils.core import setup, Extension

module1 = Extension('cgss_rijndael',
                    include_dirs = ['/usr/local/include'],
                    libraries = ['mcrypt'],
                    library_dirs = ['/usr/local/lib'],
                    extra_compile_args=['-std=c11'],
                    sources = ['rijndael.c', 'python_wrapper.c'])

setup (name = 'cgss_rijndael',
       version = '1.0',
       description = 'CGSS MCrypt Rijndael Ext.',
       author = 'Sam Lee',
       author_email = 'me@shibuya-rin.moe',
       url = 'https://docs.python.org/extending/building',
       long_description = '''
MCrypt Rijndael256-CBC Implementation for Deresute transmission data encrypt/decrypt.
''',
       ext_modules = [module1])