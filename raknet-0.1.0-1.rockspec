package = "raknet"
version = "0.1.0-1"

source = {
  url = "git://github.com/reasonMix/RakNet.git",
  tag = "v0.1.0"
}
description={
   summary = 'raknet',
   detailed = 'raknet',
   homepage = "https://github.com/reasonMix/RakNet",
   license = "The MIT License"
}
dependencies = { "lua >= 5.1" }
build = {
  type = 'cmake',
  platforms = {
     windows = {
        variables = {
           LUA_LIBRARIES = '$(LUA_LIBDIR)/$(LUALIB)'
        }
     }
  },
  variables = {
    BUILD_SHARED_LIBS = 'ON',
    CMAKE_INSTALL_PREFIX = '$(PREFIX)',
    LUA_INCLUDE_DIR = '$(LUA_INCDIR)',
  }
}
