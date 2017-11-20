/*
 *   Xerox Research Centre Europe - Grenoble Laboratory
 *           project ATANOR
 *  Copyright (C) 2017 Xerox Corporation, XRCE-Grenoble, All Rights Reserved
 *
 */
package com.xerox.jatanor

import java.io.File
import java.util
import ch.jodersky.jni.nativeLoader


/**
  * Description of the Class
  *
  * @author roux @created January 23, 2017
  */
class JAtanor() {

  val dynLoaderFromJar = new DynLoaderFromJar
  dynLoaderFromJar.loadLibFromJar()
  
  @native @throws[Exception]
  def LoadProgramImplementation(filename: String, args: String):Int

  /**
    * Load an Atanor program
    *
    * @param filename of the Atanor program to load
    * @param args     arguments as a string, where each parameter is separated with a space
    * @return
    * @exception Exception
    */
  @throws[Exception]
  def LoadProgram(filename: String, args: String): Int = LoadProgramImplementation(filename, args)

  @native @throws[Exception]
  def ExecuteFunctionImplementation(handler: Int, code: String, args: Array[String]): String

  /**
    * Execute an Atanor program from String
    *
    * @param code of the KiF program to execute
    * @param args arguments as a string, where each parameter is separated with a space
    * @return
    * @exception Exception
    */
  @throws[Exception]
  def ExecuteFunction(handler: Int, code: String, args: Array[String]): String = ExecuteFunctionImplementation(handler, code, args)

  @native @throws[Exception]
  def ExecuteFunctionArrayImplementation(handler: Int, code: String, args: Array[String]): Array[String]

  @throws[Exception]
  def ExecuteFunctionArray(handler: Int, code: String, args: Array[String]): Array[String] = ExecuteFunctionArrayImplementation(handler, code, args)
}
