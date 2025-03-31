python3 = import('python').find_installation()

cmd_py = '''
import glob

sources = glob.glob('@0@/src/**/*.cpp', recursive=True)
sources += glob.glob('@0@/src/**/*.h', recursive=True)

for i in sources:
  print(i)
'''.format(meson.project_source_root())

all_CPP_sources = run_command(
  python3, 
  '-c', 
  cmd_py
).stdout().strip().split('\n')
