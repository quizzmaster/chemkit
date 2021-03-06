find_package(Chemkit)
include_directories(${CHEMKIT_INCLUDE_DIRS})

find_package(Qt4 4.6 COMPONENTS QtCore QtTest REQUIRED)
set(QT_DONT_USE_QTGUI TRUE)
set(QT_USE_QTTEST TRUE)
include(${QT_USE_FILE})

add_subdirectory(alphashape)
add_subdirectory(aromaticitymodel)
add_subdirectory(aminoacid)
add_subdirectory(atom)
add_subdirectory(atomtyper)
add_subdirectory(bond)
add_subdirectory(bondpredictor)
add_subdirectory(cartesiancoordinates)
add_subdirectory(coordinatepredictor)
add_subdirectory(coordinateset)
add_subdirectory(delaunaytriangulation)
add_subdirectory(diagramcoordinates)
add_subdirectory(element)
add_subdirectory(fingerprint)
add_subdirectory(fingerprintsimilaritydescriptor)
add_subdirectory(fragment)
add_subdirectory(internalcoordinates)
add_subdirectory(isotope)
add_subdirectory(matrix)
add_subdirectory(moiety)
add_subdirectory(moleculardescriptor)
add_subdirectory(molecularsurface)
add_subdirectory(molecule)
add_subdirectory(moleculealigner)
add_subdirectory(moleculeeditor)
add_subdirectory(moleculegraphtraits)
add_subdirectory(moleculewatcher)
add_subdirectory(nucleotide)
add_subdirectory(plugin)
add_subdirectory(point3)
add_subdirectory(polymer)
add_subdirectory(quaternion)
add_subdirectory(residue)
add_subdirectory(ring)
add_subdirectory(scalarfield)
add_subdirectory(stereochemistry)
add_subdirectory(structuresimilaritydescriptor)
add_subdirectory(substructurequery)
add_subdirectory(variant)
add_subdirectory(vector3)
