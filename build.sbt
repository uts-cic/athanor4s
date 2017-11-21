name := "athanor4s"
version := "0.1.0"
enablePlugins(GitVersioning)

// Java Native Interface 
// used to generate native (C++) header files 
// and compile C++ parts which interface to the C++ athanor DLL
enablePlugins(JniNative)

// Location of generated JNI header file. 
target in javah := (sourceDirectory in nativeCompile).value 

// Used for Logging 
libraryDependencies += "org.slf4j" % "slf4j-simple" % "1.7.12"

lazy val commonSettings = Seq(
  version in ThisBuild := "0.1.0",
  organization in ThisBuild := "io.nlytx"
)
lazy val root = (project in file("."))
  .settings(
    commonSettings,
    sbtPlugin := true,
    name := "athanor4s",
    description := "Athanor-Server to athanor interface",
    licenses += ("Apache-2.0", url("https://www.apache.org/licenses/LICENSE-2.0.html")),
    publishMavenStyle := false,
    bintrayRepository := "sbt-plugins",
    bintrayOrganization in bintray := None
  )



