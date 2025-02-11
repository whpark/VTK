/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkProcessIdScalars.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkProcessIdScalars
 * @brief   Sets cell or point scalars to the processor rank.
 *
 *
 * vtkProcessIdScalars is meant to display which processor owns which cells
 * and points.  It is useful for visualizing the partitioning for
 * streaming or distributed pipelines.
 *
 * @sa
 * vtkPolyDataStreamer
 */

#ifndef vtkProcessIdScalars_h
#define vtkProcessIdScalars_h

#include "vtkDataSetAlgorithm.h"
#include "vtkFiltersParallelModule.h" // For export macro

VTK_ABI_NAMESPACE_BEGIN
class vtkFloatArray;
class vtkIntArray;
class vtkMultiProcessController;

class VTKFILTERSPARALLEL_EXPORT vtkProcessIdScalars : public vtkDataSetAlgorithm
{
public:
  static vtkProcessIdScalars* New();

  vtkTypeMacro(vtkProcessIdScalars, vtkDataSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  ///@{
  /**
   * Option to centerate cell scalars of points scalars.  Default is point
   * scalars (0).
   */
  void SetScalarModeToCellData() { this->SetCellScalarsFlag(1); }
  void SetScalarModeToPointData() { this->SetCellScalarsFlag(0); }
  vtkSetMacro(CellScalarsFlag, int);
  int GetScalarMode() { return this->CellScalarsFlag; }
  ///@}

  ///@{
  /**
   * This option uses a random mapping between pieces and scalar values.
   * The scalar values are chosen between 0 and 1.  By default, random
   * mode is off.
   */
  vtkSetMacro(RandomMode, vtkTypeBool);
  vtkGetMacro(RandomMode, vtkTypeBool);
  vtkBooleanMacro(RandomMode, vtkTypeBool);
  ///@}

  ///@{
  /**
   * By default this filter uses the global controller,
   * but this method can be used to set another instead.
   */
  virtual void SetController(vtkMultiProcessController*);
  vtkGetObjectMacro(Controller, vtkMultiProcessController);
  ///@}

protected:
  vtkProcessIdScalars();
  ~vtkProcessIdScalars() override;

  // Append the pieces.
  int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;

  vtkIntArray* MakeProcessIdScalars(int piece, vtkIdType numScalars);
  vtkFloatArray* MakeRandomScalars(int piece, vtkIdType numScalars);

  int CellScalarsFlag;
  vtkTypeBool RandomMode;

  vtkMultiProcessController* Controller;

private:
  vtkProcessIdScalars(const vtkProcessIdScalars&) = delete;
  void operator=(const vtkProcessIdScalars&) = delete;
};

VTK_ABI_NAMESPACE_END
#endif
