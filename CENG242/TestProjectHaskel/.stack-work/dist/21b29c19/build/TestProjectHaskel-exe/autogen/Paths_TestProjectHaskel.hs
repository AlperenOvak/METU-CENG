{-# LANGUAGE CPP #-}
{-# LANGUAGE NoRebindableSyntax #-}
{-# OPTIONS_GHC -fno-warn-missing-import-lists #-}
module Paths_TestProjectHaskel (
    version,
    getBinDir, getLibDir, getDynLibDir, getDataDir, getLibexecDir,
    getDataFileName, getSysconfDir
  ) where

import qualified Control.Exception as Exception
import Data.Version (Version(..))
import System.Environment (getEnv)
import Prelude

#if defined(VERSION_base)

#if MIN_VERSION_base(4,0,0)
catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
#else
catchIO :: IO a -> (Exception.Exception -> IO a) -> IO a
#endif

#else
catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
#endif
catchIO = Exception.catch

version :: Version
version = Version [0,1,0,0] []
bindir, libdir, dynlibdir, datadir, libexecdir, sysconfdir :: FilePath

bindir     = "C:\\Users\\OVAK\\Desktop\\c\\METU-CENG\\CENG242\\TestProjectHaskel\\.stack-work\\install\\1d469a7c\\bin"
libdir     = "C:\\Users\\OVAK\\Desktop\\c\\METU-CENG\\CENG242\\TestProjectHaskel\\.stack-work\\install\\1d469a7c\\lib\\x86_64-windows-ghc-8.8.4\\TestProjectHaskel-0.1.0.0-Hb4IwBNp1RiHiP8JrMb9AC-TestProjectHaskel-exe"
dynlibdir  = "C:\\Users\\OVAK\\Desktop\\c\\METU-CENG\\CENG242\\TestProjectHaskel\\.stack-work\\install\\1d469a7c\\lib\\x86_64-windows-ghc-8.8.4"
datadir    = "C:\\Users\\OVAK\\Desktop\\c\\METU-CENG\\CENG242\\TestProjectHaskel\\.stack-work\\install\\1d469a7c\\share\\x86_64-windows-ghc-8.8.4\\TestProjectHaskel-0.1.0.0"
libexecdir = "C:\\Users\\OVAK\\Desktop\\c\\METU-CENG\\CENG242\\TestProjectHaskel\\.stack-work\\install\\1d469a7c\\libexec\\x86_64-windows-ghc-8.8.4\\TestProjectHaskel-0.1.0.0"
sysconfdir = "C:\\Users\\OVAK\\Desktop\\c\\METU-CENG\\CENG242\\TestProjectHaskel\\.stack-work\\install\\1d469a7c\\etc"

getBinDir, getLibDir, getDynLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getBinDir = catchIO (getEnv "TestProjectHaskel_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "TestProjectHaskel_libdir") (\_ -> return libdir)
getDynLibDir = catchIO (getEnv "TestProjectHaskel_dynlibdir") (\_ -> return dynlibdir)
getDataDir = catchIO (getEnv "TestProjectHaskel_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "TestProjectHaskel_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "TestProjectHaskel_sysconfdir") (\_ -> return sysconfdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "\\" ++ name)
