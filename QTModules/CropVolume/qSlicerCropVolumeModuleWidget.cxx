// Qt includes
#include <QDebug>

// SlicerQt includes
#include "qSlicerCropVolumeModuleWidget.h"
#include "qMRMLNodeFactory.h"
#include "ui_qSlicerCropVolumeModule.h"
#include "vtkMRMLAnnotationROINode.h"

//-----------------------------------------------------------------------------
class qSlicerCropVolumeModuleWidgetPrivate: public Ui_qSlicerCropVolumeModule
{
public:
  qSlicerCropVolumeModuleWidgetPrivate();
};

//-----------------------------------------------------------------------------
// qSlicerCropVolumeModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerCropVolumeModuleWidgetPrivate::qSlicerCropVolumeModuleWidgetPrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerCropVolumeModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerCropVolumeModuleWidget::qSlicerCropVolumeModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerCropVolumeModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerCropVolumeModuleWidget::~qSlicerCropVolumeModuleWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerCropVolumeModuleWidget::setup()
{
  Q_D(qSlicerCropVolumeModuleWidget);
  d->setupUi(this);
  this->Superclass::setup();

  connect( d->InputROIComboBox->nodeFactory(), 
    SIGNAL(nodeInitialized(vtkMRMLNode*)),
    this, SLOT(initializeNode(vtkMRMLNode*)));
}

void qSlicerCropVolumeModuleWidget::initializeNode(vtkMRMLNode *n)
{
  std::cerr << "Initializing the node in crop volume" << std::endl;
  vtkMRMLScene* scene = qobject_cast<qMRMLNodeFactory*>(this->sender())->mrmlScene();
  vtkMRMLAnnotationROINode::SafeDownCast(n)->Initialize(scene);
}