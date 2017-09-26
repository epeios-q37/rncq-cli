/*
	Copyright (C) 2016 by Claude SIMON (http://zeusw.org/epeios/contact.html).

	This file is part of 'RNCq.

    'RNCq' is free software: you can redistribute it and/or modify it
    under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    'RNCq' is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with 'RNCq'.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef RNCCMN_INC_
# define RNCCMN_INC_

# include "rncflt.h"
# include "rncrtn.h"

# include "bso.h"
# include "stkbch.h"
# include "xtf.h"

namespace rnccmn {
	typedef stkbch::qBSTACKdl( bso::sChar ) dOperators;
	qW( Operators );

	inline void SkipSpaces_( xtf::sIFlow &Flow )
	{
		while ( !Flow.EndOfFlow() && ( Flow.View() == ' ' ) )
			Flow.Get();
	}

	template <typename wnumber, typename dnumbers> bso::sBool Handle_(
		dnumbers &Numbers,
		bso::sChar Operator )
	{
		bso::sBool Success = true;
		qRH
			wnumber Op1, Op2, Result;
		qRB
			if ( Numbers.Amount() < 2 )
				qRFwk();

		Op1.Init();
		Op2.Init();

		Result.Init();

		Numbers.Pop( Op2 );
		Numbers.Pop( Op1 );

		switch ( Operator ) {
		case '+':
			rnc::Add_( Op1, Op2, Result );
			break;
		case '-':
			rnc::Sub_( Op1, Op2, Result );
			break;
		case '*':
		case 'x':
			rnc::Mul_( Op1, Op2, Result );
			break;
		case ':':
		case '/':
			rnc::Div_( Op1, Op2, Result );
			break;
		default:
			Success = false;
			break;
		}

		Numbers.Push( Result );
		qRR
			qRT
			qRE
			return Success;
	}
}

#endif
