/*
 *   Xerox Research Centre Europe - Grenoble Laboratory
 *           project XIP (Xerox Incremental Parser)
 *  Copyright (C) 2004 - 2009 Xerox Corporation, XRCE-Grenoble, All Rights Reserved
 *
 */
package com.xerox.jatanor
import scala.collection.mutable.ArrayBuffer
import java.io.BufferedOutputStream
import java.io.File
import java.io.FileOutputStream
import java.io.IOException
import java.io.InputStream
import java.net.URL
import java.util.Date
import java.util
import java.util.Properties
import java.util.jar.Attributes
import java.util.jar.JarFile
import java.util.jar.Manifest

//slf4j Logging classes
import org.slf4j.Logger
import org.slf4j.LoggerFactory


/**
  * The purpose of this class is to load the dynamic libs.
  *
  * @author roux @created January 23, 2017
  * Ported to Scala and modified for the athanor4s project November 20, 2017 
  */
class DynLoaderFromJar {
  private var tmpDir:File = null
  private var libNamesWindows = ArrayBuffer[String]()
  private var offsetWindows:String=null
  private var offsetWindows64:String=null
  private var libNamesLinux = ArrayBuffer[String]()
  private var offsetLinux:String=null
  private var offsetLinux64:String=null
  private var libNamesSolaris = ArrayBuffer[String]()
  private var offsetSolaris:String=null
  private var libNamesMac = ArrayBuffer[String]()
  private var offsetMac:String=null
  val   logger = LoggerFactory.getLogger("athanor4s")

  def loadLibFromJar(): Unit = { //System.out.println("DynLoaderFromJar()");
    DynLoaderFromJarCommon(null)
  }

  def loadLibFromJar(libs: ArrayBuffer[String], loadingLibInJar: Boolean): Unit = {
    for (libPath <- libs) {
      try
        if (new File(libPath).exists) { 
          logger.info("DynLoaderFromJar  loading: {}", libPath);
          System.load(libPath)
        }
        else 
          logger.error("The lib does not exist: {}", libPath)
      catch {
        case ex: Throwable =>
          logger.error("Exception during loading: {}", libPath)
          logger.error("Exception: {}", ex)
          throw new RuntimeException("DynLoaderFromJar:" + ex.toString)
      }
    }
    if (loadingLibInJar) DynLoaderFromJarCommon(null)
  }

  private def DynLoaderFromJarCommon(jarFile: String): Unit = { 
    createTmpDir()
    init()
    loadNativeLibraries(jarFile)
    //deleteTmpDir();
  }

  private def init(): Unit = {
    logger.trace("-->init")
    val inputStream = classOf[DynLoaderFromJar].getResourceAsStream("/init.properties")
    offsetWindows = "windows"

    offsetWindows64 = "windows64"
 
    offsetLinux = "linux"
 
    offsetLinux64 = "native/x86_64-linux"
 

    offsetSolaris = "solaris5.10-x86"
    offsetMac = "mac-i386"
 
    libNamesWindows += "athanor.dll"
 
    libNamesLinux += "libathanor.so"
 
    libNamesSolaris += "libathanor.so"
 
    libNamesMac += "libathanor.so"
  }

  def is64BitVM: Boolean = {
    val bits = System.getProperty("sun.arch.data.model", "?")
    logger.info("++++++++++++++++++ bits = {}", bits)
    logger.info("++++++++++++++++++ java.vm.name={}", System.getProperty("java.vm.name"))
 
    if (bits == "64") return true
    if (bits == "?") { // probably sun.arch.data.model isn't available
      // maybe not a Sun JVM?
      // try with the vm.name property
      return System.getProperty("java.vm.name").toLowerCase.contains("64")
    }
    // probably 32bit
    false
  }

  def isWindows: Boolean = {
    val windowsStr = "Windows"
    var osName = System.getProperty("os.name")
    if (osName.length >= windowsStr.length) osName = osName.substring(0, windowsStr.length)
    osName == windowsStr
  }

  def isLinux: Boolean = System.getProperty("os.name") == "Linux"

  def isSolaris: Boolean = System.getProperty("os.name") == "SunOS"

  def isMac: Boolean = (System.getProperty("os.name") == "Mac OS X") || (System.getProperty("os.name") == "Darwin")

  /**
    * call loadDynamicLibFromJar with the right parameters
    *
    * @param jarFile Description of the Parameter
    */
  private def loadNativeLibraries(jarFile: String): Unit = { 
    logger.trace("-->loadNativeLibraries\n");
    if (isWindows) if (is64BitVM) loadDynamicLibFromJar(offsetWindows64, libNamesWindows, jarFile)
    else loadDynamicLibFromJar(offsetWindows, libNamesWindows, jarFile)
    else if (isSolaris) loadDynamicLibFromJar(offsetSolaris, libNamesSolaris, jarFile)
    else if (isLinux)
    { 
      logger.debug("Linux")  
      if (is64BitVM) 
      {
        logger.debug("-- 64 bits\n")
        loadDynamicLibFromJar(offsetLinux64, libNamesLinux, jarFile)
        logger.debug("Libray Loaded\n");
      }
      else
      {
        logger.debug("-- 32 bits\n")
        loadDynamicLibFromJar(offsetLinux, libNamesLinux, jarFile)
        logger.debug("Libray Loaded\n");

      } 
    } else if (isMac) loadDynamicLibFromJar(offsetMac, libNamesMac, jarFile)
    else throw new RuntimeException("unknow os:    os.name = " + System.getProperty("os.name"))
    logger.trace("<--loadNativeLibraries\n");
  }

  /**
    * create a temporary dir
    */
  def createTmpDir(): Unit = {
    var tmpDirStr = System.getProperty("java.io.tmpdir")
    if (!tmpDirStr.endsWith(File.separator)) tmpDirStr += File.separator
    tmpDirStr += System.getProperty("user.name")
    tmpDirStr += File.separator + getBuildDateInManifest
    tmpDir = new File(tmpDirStr)
    if (!tmpDir.exists) {
      tmpDir.mkdirs
      tmpDir.deleteOnExit()
    }
    logger.info("createTmpDir() tmpDir = {}" , tmpDir.getAbsolutePath());
  }

  /**
    * return a String which is the date of the jar build (or the current date ,
    * if the jar build date can't be found)
    */
  private def getBuildDateInManifest = {
    var resEnum = null
    var jarBuildDate = new Date().getTime //default value
    // the default value must be avoided because on windows this create a lot of temporary directories which are not destroy on exit(bug??)
    // so the solution is to create a temporary dir which depends on the building date of the jar (extracted from the manifest)
    try {
      val resEnum = Thread.currentThread.getContextClassLoader.getResources(JarFile.MANIFEST_NAME)
      // there is certainly more than one Manifest.mf file (the class loader get all the resources from all the jar used in the application)
      var foundManifest = false
      while ((resEnum.hasMoreElements) && (!foundManifest)) {
        val url = resEnum.nextElement.asInstanceOf[URL]
        logger.info("url: {}", url.toString());
        //if (url.getPath().contains("jatanor.jar!")) {
        val is = url.openStream
        if (is != null) {
          val manifest = new Manifest(is)
          val attributes = manifest.getMainAttributes
          if ("com.xerox.jatanor.JXip" == attributes.getValue("Main-class")) { //it's the manifest file included in jatanor.jar
            val jarBuildDate = attributes.getValue("Built-Date")
            logger.info("jarBuildDate: {}", jarBuildDate);
            foundManifest = true
          }
        }
      }
    } catch {
      case ex: Exception =>
        logger.error("ex: {}", ex)
    }
    jarBuildDate
  }

  /**
    * delete the temporary dir
    */
  def deleteTmpDir(): Unit = {
    logger.trace("deleteTmpDir() tmpDir = {}", tmpDir.getAbsolutePath());
    val children = tmpDir.list()
    for (children1 <- children) { //delete all the files in the tmpDir
      val file = new File(tmpDir, children1)
      file.deleteOnExit()
      file.delete
    }
    tmpDir.deleteOnExit()
    tmpDir.delete
  }

  /**
    * extract a list of native libraries(*.dll or *.so) from the jar file,
    * store each of them in a temporary directory, and call System.load for
    * each temporary file.
    *
    * @param jarOffset   offset in the jar to found the dynamic lib
    * @param fileNames   array of file names (dynamic library: *.dll or *.so)
    * @param jarFileName if null use the current jar, or the jar file name
    *                    where the dynamic lib are stored
    */
  private def loadDynamicLibFromJar(jarOffset: String, fileNames: ArrayBuffer[String], jarFileName: String): Unit = { 
    logger.trace("-->loadDynamicLibFromJar() jarOffset = {}", jarOffset);
    for (fileName <- fileNames) {
      logger.trace("fileName={}", fileName);
      val libPath = extractFileFromJar(jarOffset, fileName, jarFileName)
      logger.debug("libPath={}", libPath);
      try 
      {
        logger.debug("\n+++++++++++++++++loadDynamicLibFromJar System.load({})", libPath);
        System.load(libPath)
      }
      catch {
        case ex: Exception =>
          logger.error("Exception during loading: " + libPath)
          logger.error("Exception: " + ex)
          throw new RuntimeException("loadDynamicLibFromJar:" + ex.toString)
      }
    }
    logger.trace("<--loadDynamicLibFromJar()");
  }

  /**
    * extract from the jar (jarFileName) the filename at the offset in jar
    * defined by jarOffset
    *
    * @param jarOffset
    * @param fileName
    * @param jarFileName if null, extract from the current jar
    * @return a temporary file (extracted file from the jar)
    */
  def extractFileFromJar(jarOffset: String, fileName: String, jarFileName: String): String = {
    logger.trace("-->extractFileFromJar")
    logger.debug("jarOffset={},fileName={},jarFileName={}",jarOffset, fileName, jarFileName)
    var byteArray = new Array[Byte](1000000)
    var byteNb = 0
    var bufferedOutputStream:BufferedOutputStream = null
    var inputStream:InputStream = null
    var resourceName:String = null
    if (jarOffset == "") resourceName = fileName
    else resourceName = jarOffset + "/" + fileName
    logger.debug("extractFileFromJar() resourceName = {}", resourceName);
    val tempFile = tmpDir + File.separator + fileName
    logger.debug("tempFile={}",tempFile)
    if (new File(tempFile).exists) { // si le fichier exist deja ne rien faire
      logger.debug("File exists")
      tempFile
    }
    else try { 
      logger.debug("extractFileFromJar() Extract lib:{}", tempFile);
      bufferedOutputStream = new BufferedOutputStream(new FileOutputStream(tempFile))
      inputStream = null;
      if (jarFileName == null) { 
        logger.debug("extractFileFromJar() loading from jar");
        //the ressources must be extract from the jar of the application
        // use the class of the application: so we call this.getGlass() rather than getGlass()
        inputStream = classOf[DynLoaderFromJar].getResourceAsStream("/" + resourceName)
        if (inputStream == null) {
          var errMes = "extractFileFromJar() \n"
          errMes += "your classPath = " + System.getProperty("java.class.path") + "\n"
          errMes += "Could not unpack: " + resourceName
          throw new RuntimeException(errMes)
        }
        byteNb = inputStream.read(byteArray, 0, byteArray.length);
        while (byteNb >= 0) {
          bufferedOutputStream.write(byteArray, 0, byteNb)
          byteNb = inputStream.read(byteArray, 0, byteArray.length);
        }
      }
      else { //the ressources must be extract from an other jar provided in parameter
        logger.debug("extractFileFromJar() loading from external jar:{}", jarFileName);
        val jarFile = new JarFile(jarFileName)
        inputStream = jarFile.getInputStream(jarFile.getEntry(resourceName))
        while (inputStream.read(byteArray, 0, byteArray.length) >= 0)
          bufferedOutputStream.write(byteArray, 0, byteNb)
        jarFile.close()
      }
      bufferedOutputStream.close()
      inputStream.close()
      tempFile
    } catch {
      case ex@(_: RuntimeException | _: IOException) =>
        logger.error("Exception:{}", ex)
        throw new RuntimeException("extractFileFromJar:" + ex.toString)
    }
  }
}
