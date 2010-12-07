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

// Qt includes
#include <QDebug>

// CTK includes
#include "ctkLogger.h"

// QtGUI includes
#include "qSlicerCoreApplication.h"
#include "qSlicerSettingsModulesPanel.h"
#include "ui_qSlicerSettingsModulesPanel.h"

// Default defines Slicer_INSTALL_QTLOADABLEMODULES_BIN_DIR
#include <vtkSlicerConfigure.h>

static ctkLogger logger("org.commontk.libs.widgets.qSlicerSettingsModulesPanel");

//-----------------------------------------------------------------------------
class qSlicerSettingsModulesPanelPrivate: public Ui_qSlicerSettingsModulesPanel
{
  Q_DECLARE_PUBLIC(qSlicerSettingsModulesPanel);
protected:
  qSlicerSettingsModulesPanel* const q_ptr;

public:
  qSlicerSettingsModulesPanelPrivate(qSlicerSettingsModulesPanel& object);
  void init();

};

// --------------------------------------------------------------------------
qSlicerSettingsModulesPanelPrivate::qSlicerSettingsModulesPanelPrivate(qSlicerSettingsModulesPanel& object)
  :q_ptr(&object)
{
}

// --------------------------------------------------------------------------
void qSlicerSettingsModulesPanelPrivate::init()
{
  Q_Q(qSlicerSettingsModulesPanel);

  this->setupUi(q);

  this->ExtensionInstallDirectoryButton->setDirectory( qSlicerCoreApplication::application()->extensionsPath());
  this->TemporaryDirectoryButton->setDirectory( qSlicerCoreApplication::application()->temporaryPath());

  q->registerProperty("disable-loadable-module", this->LoadModulesCheckBox, "checked",
                      SIGNAL(toggled(bool)));
  q->registerProperty("disable-cli-module", this->LoadCommandLineModulesCheckBox, "checked",
                      SIGNAL(toggled(bool)));
  q->registerProperty("Modules/ExtensionsInstallDirectory", this->ExtensionInstallDirectoryButton, "directory",
                      SIGNAL(directoryChanged(const QString&)));
  q->registerProperty("Modules/TemporaryDirectory", this->TemporaryDirectoryButton, "directory",
                      SIGNAL(directoryChanged(const QString&)));

  QObject::connect(this->ExtensionInstallDirectoryButton, SIGNAL(directoryChanged(const QString&)),
                   q, SLOT(onExensionsPathChanged(const QString&)));
  QObject::connect(this->TemporaryDirectoryButton, SIGNAL(directoryChanged(const QString&)),
                   q, SLOT(onTemporaryPathChanged(const QString&)));

}

// --------------------------------------------------------------------------
qSlicerSettingsModulesPanel::qSlicerSettingsModulesPanel(QWidget* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerSettingsModulesPanelPrivate(*this))
{
  Q_D(qSlicerSettingsModulesPanel);
  d->init();
}

// --------------------------------------------------------------------------
qSlicerSettingsModulesPanel::~qSlicerSettingsModulesPanel()
{
}

// --------------------------------------------------------------------------
void qSlicerSettingsModulesPanel::onExensionsPathChanged(const QString& path)
{
  qSlicerCoreApplication::application()->setExtensionsPath(path);
}

// --------------------------------------------------------------------------
void qSlicerSettingsModulesPanel::onTemporaryPathChanged(const QString& path)
{
  qSlicerCoreApplication::application()->setTemporaryPath(path);
}