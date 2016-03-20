cmake_minimum_required(VERSION 2.8.4)

#если ругается на -std=c++11 - версия gcc != 4.8

project(qtreportsviewer)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#обязательно указать CMAKE_PREFIX_PATH "C:/Qt/5/5.5/mingw492_32" к qt5
if(!CMAKE_PREFIX_PATH)
message(WARNING "CHECK CMAKE_PREFIX_PATH")
endif()

find_package (Qt5Widgets REQUIRED )
find_package (Qt5Core REQUIRED )
find_package (Qt5Sql REQUIRED )
find_package (Qt5Gui REQUIRED )
find_package (Qt5PrintSupport REQUIRED )

include_directories(${Qt5Widgets_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS})

include_directories(${Qt5Sql_INCLUDE_DIRS})
add_definitions(${Qt5Sql_DEFINITIONS})

include_directories(${Qt5PrintSupport_INCLUDE_DIRS})
add_definitions(${Qt5PrintSupport_DEFINITIONS})

set(QT5_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets Qt5::PrintSupport Qt5::Sql)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -std=c++11 -Wall -U__STRICT_ANSI__")

if (UNIX) 
  set(QT_FULL_SPEC_DIR ${QT_MKSPECS_DIR}/linux-g++)
else()
  set(QT_FULL_SPEC_DIR ${QT_MKSPECS_DIR}/default)
endif()


SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/qtreportsviewer)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/qtreportsviewer) 


  include_directories (
    ./
	./qtreportslib/tags
	./qtreportslib/converters
	./qtreportslib
	${QT_FULL_SPEC_DIR}
	)

SET(CONVERTERS 
qtreportslib/converters/convertertohtml.cpp
qtreportslib/converters/convertertohtml.hpp
qtreportslib/converters/convertertopdf.cpp
qtreportslib/converters/convertertopdf.hpp 
qtreportslib/converters/convertertoqwidget.cpp
qtreportslib/converters/convertertoqwidget.hpp)	
	
SET(TAGS 
qtreportslib/tags/band.cpp 
qtreportslib/tags/band.hpp 
qtreportslib/tags/detail.cpp 
qtreportslib/tags/detail.hpp 
qtreportslib/tags/drawingexception.cpp 
qtreportslib/tags/drawingexception.hpp
qtreportslib/tags/field.cpp
qtreportslib/tags/field.hpp
qtreportslib/tags/querystring.cpp
qtreportslib/tags/querystring.hpp
qtreportslib/tags/object.cpp 
qtreportslib/tags/object.hpp
qtreportslib/tags/report.cpp 
qtreportslib/tags/report.hpp
qtreportslib/tags/section.cpp
qtreportslib/tags/section.hpp
qtreportslib/tags/statictext.cpp 
qtreportslib/tags/statictext.hpp
qtreportslib/tags/textfield.cpp
qtreportslib/tags/textfield.hpp
qtreportslib/tags/style.cpp 
qtreportslib/tags/style.hpp
qtreportslib/tags/title.cpp 
qtreportslib/tags/title.hpp
qtreportslib/tags/widget.cpp
qtreportslib/tags/widget.hpp)

SET (QTRLIB
qtreportslib/engine.cpp
qtreportslib/engine.hpp
qtreportslib/objectsplant.cpp
qtreportslib/objectsplant.hpp
qtreportslib/painter.cpp
qtreportslib/painter.hpp
qtreportslib/parser.cpp
qtreportslib/parser.hpp
qtreportslib/processeddb.cpp
qtreportslib/processeddb.hpp
	)
	
SET(EXE 
qtreportsviewer/main.cpp 
)

add_library ( qtreports SHARED ${TAGS} ${QTRLIB} ${CONVERTERS})

target_link_libraries ( qtreports  ${QT5_LIBRARIES})
	
SET(EXE 
qtreportsviewer/main.cpp 
)
	
add_executable (main ${EXE})
	
target_link_libraries ( main qtreports ${QT5_LIBRARIES})

	
