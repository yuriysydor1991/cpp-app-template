find_program('clang-format', required: true)

python3 = import('python').find_installation()

cmd_py = '''
import glob

sources = glob.glob('@0@/src/**/*.cpp', recursive=True)
sources += glob.glob('@0@/src/**/*.h', recursive=True)

for i in sources:
  print(i)
'''.format(meson.project_source_root())

cpp_files = run_command(
  python3, 
  '-c', 
  cmd_py
).stdout().strip()

clangformat_cmd = [
  'clang-format', 
  '--style=file:' + join_paths(meson.project_source_root(), 'misc', '.clang-format'),
  '--Werror',
  '-i'] + cpp_files.split('\n')

clangformat_target = custom_target(
  'clang-format',
  command: clangformat_cmd,
  build_always_stale: true,
  output: 'clang-format-output-stub.txt'
)
