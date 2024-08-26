cmake_minimum_required(VERSION 2.20)
project(sql_test)


set(EXTERNAL_DEPENDS
  Qt5Widgets
  Qt5PrintSupport
  #OpenCV
  )

set(EXTERNAL_DEPENDS_LIB
  Qt5::Widgets
  Qt5::PrintSupport
  Qt5::Core
  #${OpenCV_LIBS}
  )
set(CMAKE_INCLUDE_CURRENT_DIR ON)

foreach(DEPEND ${EXTERNAL_DEPENDS})
  find_package(${DEPEND} REQUIRED)
endforeach(DEPEND)


file(GLOB HDRS
  "include/*.hpp"
)
file(GLOB SRCS
  "src/*.cc"
  "src/*.hpp"
)


###
### QT stuff (required if you want a GUI)
###
set(CMAKE_AUTOMOC ON)  #This will autogenerate qt gui stuff
set(CMAKE_AUTORCC ON)  #this needs to be on so cmake will know what to do with QT resource Files


#find all the qt UI stuff
file(GLOB_RECURSE UI
    "include/*.ui"
)

message("Adding ${PROJECT_NAME} UI files: " )
foreach(source ${UI})
    message("  - " ${source})
endforeach(source)

#make them into headers
qt5_wrap_ui (UI_HDRS  ${UI})

message("Generating ${PROJECT_NAME} UI Headers: " )
foreach(source ${UI_HDRS})
    message("  - " ${source})
endforeach(source)

# find all resource files
file(GLOB QRC
    "rc/*.qrc"
)

message("buliding ${PROJECT_NAME} node: ")
set(NODE_FILE src/main.cc)


get_filename_component(NODE_NAME ${NODE_FILE} NAME_WE)
message("  - " ${NODE_NAME})

add_executable(${NODE_NAME} ${NODE_FILE} ${HDRS} ${SRCS} ${UI} ${QRC})
target_link_libraries(${NODE_NAME} ${EXTERNAL_DEPENDS_LIB} mysqlclient jsoncpp)
target_include_directories(${NODE_NAME} PRIVATE "include/")

list(APPEND NODE_LIST ${NODE_NAME})



add_executable(test_sql ./test_sql.cc)
target_link_libraries(test_sql mysqlclient)

add_executable(test_sql_rrys ./test_sql_rrys.cc)
target_link_libraries(test_sql_rrys mysqlclient)