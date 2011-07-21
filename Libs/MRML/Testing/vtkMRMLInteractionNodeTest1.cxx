/*=auto=========================================================================

  Portions (c) Copyright 2005 Brigham and Women's Hospital (BWH) 
  All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Program:   3D Slicer

=========================================================================auto=*/

#include "vtkMRMLInteractionNode.h"

#include <stdlib.h>
#include <iostream>

#include "TestingMacros.h"

int vtkMRMLInteractionNodeTest1(int , char * [] )
{
  vtkSmartPointer< vtkMRMLInteractionNode > node1 = vtkSmartPointer< vtkMRMLInteractionNode >::New();

  EXERCISE_BASIC_OBJECT_METHODS( node1 );

  EXERCISE_BASIC_MRML_METHODS(vtkMRMLInteractionNode, node1);

  TEST_SET_GET_INT_RANGE( node1, CurrentInteractionMode, 1, 7);
  TEST_SET_GET_INT_RANGE( node1, LastInteractionMode, 1, 7);

  TEST_SET_GET_INT_RANGE( node1, PickModePersistence, 0, 1);
  TEST_SET_GET_INT_RANGE( node1, PlaceModePersistence, 0, 1);
  TEST_SET_GET_INT_RANGE( node1, TransformModePersistence, 0, 1);
  
  node1->NormalizeAllMouseModes();

  const char *modeStr = node1->GetInteractionModeAsString();
  std::cout << "Interaction mode = " << (modeStr ? modeStr : "null") << std::endl;
  for (int m = 0; m < 9; m++)
    {
    modeStr = node1->GetInteractionModeAsString(m);
    std::cout << "Interaction mode " << m << " = " << (modeStr ? modeStr : "null") << std::endl;
    }
  int mode = node1->GetInteractionModeByString(NULL);
  std::cout << "For null string, interaction mode = " << mode << std::endl;
  mode = node1->GetInteractionModeByString("invalid");
  std::cout << "For 'invalid' string, interaction mode = " << mode << std::endl;
  mode = node1->GetInteractionModeByString("ViewPan");
  std::cout << "For 'ViewPan' string, interaction mode = " << mode << std::endl;
  
  node1->SwitchToPersistentPickMode();
  if (!node1->GetPickModePersistence())
    {
    std::cerr << "Error in SwitchToPersistentPickMode, got persistence = " << node1->GetPickModePersistence() << std::endl;
    return EXIT_FAILURE;
    }
  node1->SwitchToSinglePickMode();
  if (node1->GetPickModePersistence())
    {
    std::cerr << "Error in SwitchToSinglePickMode, got persistence = " << node1->GetPickModePersistence() << std::endl;
    return EXIT_FAILURE;
    }
  node1->SwitchToPersistentPlaceMode();
  if (!node1->GetPlaceModePersistence())
    {
    std::cerr << "Error in SwitchToPersistentPlaceMode, got persistence = " << node1->GetPlaceModePersistence() << std::endl;
    return EXIT_FAILURE;
    }
  node1->SwitchToSinglePlaceMode();
  if (node1->GetPlaceModePersistence())
    {
    std::cerr << "Error in SwitchToSinglePlaceMode, got persistence = " << node1->GetPlaceModePersistence() << std::endl;
    return EXIT_FAILURE;
    }
  node1->SwitchToViewTransformMode();
  if (!node1->GetTransformModePersistence())
    {
    std::cerr << "Error in SwitchToViewTransformMode, got persistence = " << node1->GetTransformModePersistence() << std::endl;
    return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
