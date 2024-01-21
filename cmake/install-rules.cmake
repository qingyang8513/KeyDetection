install(
    TARGETS KeyDetection_exe
    RUNTIME COMPONENT KeyDetection_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
