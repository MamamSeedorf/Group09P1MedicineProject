cmake_minimum_required(VERSION 3.26)
project(P1MedicineProject C)

set(CMAKE_C_STANDARD 11)

add_library(medicine src/Functions/readMedicine.c
        src/Parsers/medicineParser.c
        src/Functions/NDCinformation.c
        src/Functions/validateAnswers.c
)

add_library(patient
        src/Functions/readPatient.c
        src/Parsers/patientParser.c
        src/Functions/addPatient.c
        src/Functions/PatientInformation.c
        src/Functions/editPatient.c
        src/Functions/readLog.c
        src/Functions/findNextId.c
        src/Functions/fileOpener.c
        src/Functions/populateArray.c
        src/Functions/validateAnswers.c)

add_library(user
        src/Parsers/doctorParser.c
        src/Functions/addMedicine.c
        src/Functions/dispenser.c
        src/Functions/log.c
        src/Parsers/logParser.c
        src/Parsers/nurseParser.c
        src/Parsers/parseHelper.c
        src/Functions/validateAnswers.c
)


add_executable(P1MedicineProject
        src/main.c
        src/fileStructs/patientStruct.h
        src/fileStructs/medicineStruct.h
        src/fileStructs/logStruct.h
        src/fileStructs/nurseStruct.h
        src/fileStructs/doctorStruct.h
        src/store.h
        src/Functions/startLoginFunction.c
        src/Functions/validateAnswers.c
)
target_link_libraries(P1MedicineProject
        medicine
        patient
        user)
