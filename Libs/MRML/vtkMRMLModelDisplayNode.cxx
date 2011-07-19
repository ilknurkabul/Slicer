/*=auto=========================================================================

Portions (c) Copyright 2005 Brigham and Women's Hospital (BWH) All Rights Reserved.

See COPYRIGHT.txt
or http://www.slicer.org/copyright/copyright.txt for details.

Program:   3D Slicer
Module:    $RCSfile: vtkMRMLModelDisplayNode.cxx,v $
Date:      $Date: 2006/03/03 22:26:39 $
Version:   $Revision: 1.3 $

=========================================================================auto=*/
#include "vtkMRMLColorNode.h"
#include "vtkMRMLModelDisplayNode.h"
#include "vtkMRMLScene.h"

#include "vtkCallbackCommand.h"
#include "vtkImageData.h"
#include "vtkMatrix4x4.h"
#include "vtkObjectFactory.h"
#include <vtkPolyData.h>
#include "vtkTransform.h"

#include <string>
#include <iostream>
#include <sstream>

vtkCxxSetObjectMacro(vtkMRMLModelDisplayNode, PolyData, vtkPolyData)

//------------------------------------------------------------------------------
vtkMRMLModelDisplayNode* vtkMRMLModelDisplayNode::New()
{
  // First try to create the object from the vtkObjectFactory
  vtkObject* ret = vtkObjectFactory::CreateInstance("vtkMRMLModelDisplayNode");
  if(ret)
    {
    return (vtkMRMLModelDisplayNode*)ret;
    }
  // If the factory was unable to create the object, then create it here.
  return new vtkMRMLModelDisplayNode;
}

//-----------------------------------------------------------------------------

vtkMRMLNode* vtkMRMLModelDisplayNode::CreateNodeInstance()
{
  // First try to create the object from the vtkObjectFactory
  vtkObject* ret = vtkObjectFactory::CreateInstance("vtkMRMLModelDisplayNode");
  if(ret)
    {
    return (vtkMRMLModelDisplayNode*)ret;
    }
  // If the factory was unable to create the object, then create it here.
  return new vtkMRMLModelDisplayNode;
}

//-----------------------------------------------------------------------------
vtkMRMLModelDisplayNode::vtkMRMLModelDisplayNode()
{
  this->PolyData = NULL;
}

//-----------------------------------------------------------------------------
vtkMRMLModelDisplayNode::~vtkMRMLModelDisplayNode()
{
  if ( this->PolyData)
    {
    this->PolyData->Delete();
    }
}

//----------------------------------------------------------------------------
void vtkMRMLModelDisplayNode::Copy(vtkMRMLNode *anode)
{
  Superclass::Copy(anode);
}

