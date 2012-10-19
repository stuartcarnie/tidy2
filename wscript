from platform import system

srcdir='.'
blddir='build'
VERSION='0.0.2'

def set_options(opt):
  opt.tool_options('compiler_cxx')

def configure(conf):
  conf.check_tool('compiler_cxx')
  conf.check_tool('node_addon')
  conf.check_cfg(package='tidy', args='--cflags --libs', uselib_store='tidy')
  if system() == 'Darwin':
    conf.env.CXX = conf.env.LINK_CXX = 'clang++'
    conf.env.CXXFLAGS = [ '-std=c++11', '-stdlib=libc++' ]
  else:
    conf.env.CXXFLAGS = [ '-std=c++0x' ]

def build(bld):
  obj = bld.new_task_gen('cxx', 'shlib', 'node_addon', lib="tidy")
  obj.target = 'tidy'
  obj.source = 'node_tidy.cc'

