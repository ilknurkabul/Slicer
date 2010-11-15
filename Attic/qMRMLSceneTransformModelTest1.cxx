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

  This file was originally developed by Julien Finet, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// QT includes
#include <QApplication>
#include <QString>
#include <QStringList>

// CTK includes
#include <ctkModelTester.h>

// qMRML includes
#include "qMRMLSceneFactoryWidget.h"
#include "qMRMLSceneTransformModel.h"

#include "TestingMacros.h"
#include <vtkEventBroker.h>

// STD includes
#include <cstdlib>
#include <iostream>

int qMRMLSceneTransformModelTest1(int argc, char * argv [] )
{
  QApplication app(argc, argv);

  try
    {
    qMRMLSceneTransformModel model;
    ctkModelTester tester(&model);

    qMRMLSceneFactoryWidget sceneFactory(0);
    sceneFactory.generateScene();

    model.setMRMLScene(sceneFactory.mrmlScene());
    model.setMRMLScene(sceneFactory.mrmlScene());

    sceneFactory.generateNode();
    sceneFactory.deleteNode();
  
    sceneFactory.generateNode();
    sceneFactory.deleteNode();
  
    sceneFactory.generateNode();
    sceneFactory.generateNode();
  
    sceneFactory.deleteNode();
    sceneFactory.deleteNode();
  
    sceneFactory.generateNode();
    sceneFactory.deleteNode();
  
    sceneFactory.generateNode();
    sceneFactory.deleteNode();
  
    sceneFactory.generateNode();
    sceneFactory.generateNode();
  
    sceneFactory.deleteNode();
    sceneFactory.deleteNode();

    for( int i = 0; i < 100; ++i)
      {
      sceneFactory.deleteNode();
      }
    for( int i = 0; i < 100; ++i)
      {
      sceneFactory.generateNode();
      }
    for( int i = 0; i < 99; ++i)
      {
      sceneFactory.deleteNode();
      }
    }
  catch (const char* error)
    {
    std::cerr << error << std::endl;
    return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
