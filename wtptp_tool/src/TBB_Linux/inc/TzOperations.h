/******************************************************************************
 *
 *  (C)Copyright 2005 - 2009 Marvell. All Rights Reserved.
 *  
 *  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF MARVELL.
 *  The copyright notice above does not evidence any actual or intended 
 *  publication of such source code.
 *  This Module contains Proprietary Information of Marvell and should be
 *  treated as Confidential.
 *  The information in this file is provided for the exclusive use of the 
 *  licensees of Marvell.
 *  Such users have the right to use, modify, and incorporate this code into 
 *  products for purposes authorized by the license agreement provided they 
 *  include this notice and the associated copyright notice with any such
 *  product. 
 *  The information in this file is provided "AS IS" without warranty.
 *
 ******************************************************************************/
 /********************************************************************************
Marvell BSD License Option

If you received this File from Marvell, you may opt to use, redistribute and/or
modify this File under the following licensing terms.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.

	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.

	* Neither the name of Marvell nor the names of its contributors may be
	  used to endorse or promote products derived from this software without
	  specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/

#ifndef __TZ_OPERATIONS_H__
#define __TZ_OPERATIONS_H__

#include "ErdBase.h"
#include "TimLib.h"

class CTzOperation: public CTimLib {
public:
	CTzOperation();
	CTzOperation(TZ_OPERATION_SPEC_T OpId, const string & sOpIdText);
	virtual ~CTzOperation(void);

	// copy constructor
	CTzOperation(const CTzOperation& rhs);
	// assignment operator
	CTzOperation& operator=(const CTzOperation& rhs);

	bool ToBinary(ofstream& ofs);

	bool SetOperationID(TZ_OPERATION_SPEC_T eOpId);
	bool SetOperationID(string& sOpIdText);

	TZ_OPERATION_SPEC_T m_OperationId;
	string m_sOpIdText;
	unsigned int m_Value;

	enum eTzOperationFields {
		TZ_OP_ID, TZ_OP_FIELDS_MAX
	};
};

typedef list<CTzOperation*> t_TzOperationList;
typedef list<CTzOperation*>::iterator t_TzOperationListIter;

class CTzOperations: public CErdBase {
public:
	CTzOperations();
	virtual ~CTzOperations(void);

	// copy constructor
	CTzOperations(const CTzOperations& rhs);
	// assignment operator
	virtual CTzOperations& operator=(const CTzOperations& rhs);

	virtual void Reset();

	static const string Begin;	// "TZ Operations"
	static const string End;	// "End TZ Operations"
	virtual const string& PackageName() {
		return Begin;
	}

	virtual bool Parse(CTimDescriptor& TimDescriptor,
			CTimDescriptorLine*& pLine, bool bIsBlf);

	virtual bool ToBinary(ofstream& ofs);
	virtual unsigned int PackageSize();
	virtual int AddPkgStrings(CReservedPackageData* pRPD);

	unsigned int NumOps() {
		return (unsigned int) m_TzOperationsList.size();
	}

	enum eNumFields {
		OPERATIONS_MAX = 0
	};
	t_TzOperationList m_TzOperationsList;

	static t_TzOperationList s_DefinedTzOperations;
	static int s_TzOpCount;
};

#endif //__TZ_OPERATIONS_H__
