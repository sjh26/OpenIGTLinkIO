#include "vtkObjectFactory.h"
#include "vtkMRMLTextNode.h"

//----------------------------------------------------------------------------
vtkMRMLNodeNewMacro(vtkMRMLTextNode);

//-----------------------------------------------------------------------------
vtkMRMLTextNode::vtkMRMLTextNode()
{
  this->Text = NULL;
  this->Encoding = ENCODING_US_ASCII;
}

//-----------------------------------------------------------------------------
vtkMRMLTextNode::~vtkMRMLTextNode()
{
  this->SetText(NULL);
}

//----------------------------------------------------------------------------
void vtkMRMLTextNode::ReadXMLAttributes(const char** atts)
{
  int disabledModify = this->StartModify();
  Superclass::ReadXMLAttributes(atts);

  const char* attName;
  const char* attValue;
  while (*atts != NULL)
    {
    attName = *(atts++);
    attValue = *(atts++);
    if (!strcmp(attName, "text"))
      {
      this->SetText( vtkMRMLNode::URLDecodeString(attValue) );
      }
    else if (!strcmp(attName, "encoding"))
      {
      std::stringstream ss;
      ss << attValue;
      int encoding=0;
      ss >> encoding;
      if (encoding>=3)
        {
        this->SetEncoding(encoding);
        }
      else
        {
        vtkErrorMacro("Failed to set encoding. Invalid input value: "<<attValue);
        }
      }
    }

  this->EndModify(disabledModify);
}

//----------------------------------------------------------------------------
void vtkMRMLTextNode::WriteXML(ostream& of, int nIndent)
{
  Superclass::WriteXML(of, nIndent);

  vtkIndent indent(nIndent);

  of << indent << " text=\"";
  if (this->GetText()!=NULL)
  {
    of << vtkMRMLNode::URLEncodeString(this->GetText());
  }
  of << "\"";

  of << indent << " encoding=\"" << this->GetEncoding() << "\"";
}

//----------------------------------------------------------------------------
void vtkMRMLTextNode::Copy(vtkMRMLNode *anode)
{
  int disabledModify = this->StartModify();
  Superclass::Copy(anode);
  vtkMRMLTextNode *node = vtkMRMLTextNode::SafeDownCast(anode);

  this->SetText(node->GetText());
  this->SetEncoding(node->GetEncoding());

  this->EndModify(disabledModify);
}

//----------------------------------------------------------------------------
void vtkMRMLTextNode::PrintSelf(ostream& os, vtkIndent indent)
{
  Superclass::PrintSelf(os,indent);

  os << "Text: " << ( (this->GetText()) ? this->GetText() : "None" ) << "\n";
  os << "Encoding: " << this->GetEncoding() << "\n";
}

