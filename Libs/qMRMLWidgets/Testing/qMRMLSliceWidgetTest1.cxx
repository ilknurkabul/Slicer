/*==============================================================================

  Program: 3D Slicer

  Copyright (c) 2010 Kitware Inc.

  See Doc/copyright/copyright.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// QT includes
#include <QApplication>
#include <QTimer>

// qMRML includes
#include "qMRMLSliceWidget.h"
#include "qMRMLNodeObject.h"

// MRML includes
#include <vtkMRMLColorTableNode.h>
#include <vtkMRMLScene.h>
#include <vtkMRMLSliceNode.h>
#include <vtkMRMLVolumeNode.h>

// VTK includes
#include <vtkSmartPointer.h>
#include <vtkMultiThreader.h>
// STD includes
#include <cstdlib>
#include <iostream>

int qMRMLSliceWidgetTest1(int argc, char * argv [] )
{
  QApplication app(argc, argv);
  vtkMultiThreader::SetGlobalMaximumNumberOfThreads(1);
  if( argc < 2 )
    {
    std::cerr << "Error: missing arguments" << std::endl;
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "  inputURL_scene.mrml " << std::endl;
    return EXIT_FAILURE;
    }

  vtkSmartPointer<vtkMRMLScene> scene = vtkSmartPointer<vtkMRMLScene>::New();
  scene->SetURL(argv[1]);
  scene->Connect();
  if (scene->GetNumberOfNodes() == 0)
    {
    std::cerr << "Can't load scene:" << argv[1] << " error: " <<scene->GetErrorMessage() << std::endl;
    return EXIT_FAILURE;
    }
  scene->InitTraversal();
  vtkMRMLSliceNode* sliceNode = vtkMRMLSliceNode::SafeDownCast(
    scene->GetNextNodeByClass("vtkMRMLSliceNode"));
  if (!sliceNode)
    {
    std::cerr << "Scene must contain a valid vtkMRMLSliceNode:" << sliceNode << std::endl;
    return EXIT_FAILURE;
    }
  scene->InitTraversal();
  vtkMRMLNode* node = scene->GetNextNodeByClass("vtkMRMLScalarVolumeNode");
  vtkMRMLVolumeNode* volumeNode = vtkMRMLVolumeNode::SafeDownCast(node);
  if (!volumeNode)
    {
    std::cerr << "Scene must contain a valid vtkMRMLVolumeNode:" << node << std::endl;
    return EXIT_FAILURE;
    }
  if (!volumeNode->GetDisplayNode()->GetColorNode())
    {
    // add a custom color node (grey)
    vtkMRMLColorTableNode* colorNode = vtkMRMLColorTableNode::New();
    colorNode->SetTypeToGrey();
    scene->AddNode(colorNode);
    colorNode->Delete();
    volumeNode->GetDisplayNode()->SetAndObserveColorNodeID(colorNode->GetID());
    }

  qMRMLSliceWidget sliceWidget;
  sliceWidget.setMRMLScene(scene);
  sliceWidget.setMRMLSliceNode(sliceNode);
  sliceWidget.show();
  
  qMRMLNodeObject nodeObject(volumeNode, &sliceWidget);
  QTimer modifyTimer;
  modifyTimer.setInterval(2000);
  QObject::connect(&modifyTimer, SIGNAL(timeout()),
                   &nodeObject, SLOT(modify()));
  //modifyTimer.start();
  if (argc < 3 || QString(argv[2]) != "-I" )
    {
    QTimer::singleShot(200, &app, SLOT(quit()));
    }
  return app.exec();
}
