// cedar_read_flat.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include "CedarBlock.h"
#include "CedarFile.h"
#include "CedarFlat.h"
#include "cedar_read_flat.h"
#include "CedarException.h"
#include "CedarStringConversions.h"
#include "CedarConstraintEvaluator.h"
#include "cedar_read_descriptors.h"
#include "CedarParameter.h"
#include "CedarReadParcods.h"

#ifdef __GNUG__
#include <strstream>
#else
#include <sstream>
#endif

// This is the size to right format string and pad them with blanks up to seven chars.
#define PRINTING_BLOCK_SIZE 9 

void print_blocked(ostrstream &oss, string s)
{
    int l=s.length();
    if (l>PRINTING_BLOCK_SIZE)
    {
	char errs[256] ;
	sprintf( errs, "%s %d\n%s %s\n",
	         "Trying to print block larger than",
		 PRINTING_BLOCK_SIZE,
		 "Current block is ", s.c_str() ) ;
	throw CedarException( 0, errs ) ;
    }
    for (int q=0; q<(PRINTING_BLOCK_SIZE-l); q++)
	oss<<" ";
    oss<<s<<flush;
}

void print_blocked(ostrstream &oss, long l)
{
    char temp[100];
    CedarStringConversions::ltoa(l,temp, 10);
    string s(temp);
    int len=s.length();
    if (len>PRINTING_BLOCK_SIZE)
    {
	char errs[256] ;
	sprintf( errs, "%s %d\n%s %s\n",
	         "Trying to print block larger than",
		 PRINTING_BLOCK_SIZE,
		 "Current block is ", s.c_str() ) ;
	throw CedarException( 0, errs ) ;
    }
    for (int q=0; q<(PRINTING_BLOCK_SIZE-len); q++)
	oss<<" ";
    oss<<s<<flush;
}
      
void send_flat_data(CedarFlat &cf, CedarDataRecord &dr,CedarConstraintEvaluator &qa)
{
    if (qa.validate_record(dr))
    {
	ostrstream oss;
	unsigned int w = 0 ;
	int y,z = 0 ;
	CedarDate bdate,edate;
	dr.get_record_begin_date(bdate);
	dr.get_record_end_date(edate);
	print_blocked(oss, "KINST");
	print_blocked(oss, "KINDAT");
	print_blocked(oss, "IBYRT");
	print_blocked(oss, "IBDTT");
	print_blocked(oss, "IBHMT");
	print_blocked(oss, "IBCST");
	print_blocked(oss, "IEYRT");
	print_blocked(oss, "IEDTT");
	print_blocked(oss, "IEHMT");
	print_blocked(oss, "IECST");
	print_blocked(oss, "NROWS");

	unsigned int jpar_value=dr.get_jpar();
	short int *pJparVars =new short int[jpar_value];
	if( !pJparVars )
	{
	    throw bad_alloc() ;
	}
	dr.load_JPAR_vars(pJparVars);

	for (w=0; w<jpar_value; w++)
	{ 
	    string JparVarName="";
	    string the_var="";
	    if (qa.validate_parameter(pJparVars[w]))
	    {
		int val;
		if (pJparVars[w]<0)
		{
		    val=pJparVars[w]*-1;
		    the_var+="e_";
		}
		else
		{
		    val=pJparVars[w];
		}
		get_name_for_parameter(JparVarName,val);
		the_var+=JparVarName;
		print_blocked(oss, the_var);
	    }
	}

	int mpar_value=dr.get_mpar();
	short int *pMparVars=0;
	if (mpar_value > 0 )
	{
	    pMparVars=new short int [mpar_value];
	    dr.load_MPAR_vars(pMparVars);
	    for (y=0; y<mpar_value;y++)
	    {
		string MparVarName="";
		string the_var="";
		if (qa.validate_parameter(pMparVars[y]))
		{
		    int val;
		    if (pMparVars[y]<0)
		    {
			val=pMparVars[y]*-1;
			the_var+="e_";
		    }
		    else
		    {
			val=pMparVars[y];
		    }
		    get_name_for_parameter(MparVarName,val);
		    the_var+=MparVarName;
		    print_blocked(oss, the_var);
		}
	    }
	}
	else if(mpar_value < 0 )
	{
	    cerr<<__FILE__<<":"<<__LINE__<<": found a negative MPAR value."<<endl;
	    throw CedarException(0,"negative MPAR value");
	}
	oss<<endl;

	print_blocked(oss, "N/A");
	print_blocked(oss, "N/A");
	print_blocked(oss, "1.");
	print_blocked(oss, "1.");
	print_blocked(oss, "1.");
	print_blocked(oss, "1.E-02");
	print_blocked(oss, "1.");
	print_blocked(oss, "1.");
	print_blocked(oss, "1.");
	print_blocked(oss, "1.E-02");
	print_blocked(oss, "1.");

	for (w=0; w<jpar_value; w++)
	{ 
	    if (qa.validate_parameter(abs(pJparVars[w])))
	    {
		CedarReadParcods afx;
		string element = (string)afx.get_PCSFCT(pJparVars[w]);// + string(" ") + (string) afx.get_PCULBL(pJparVars[w]);
		print_blocked(oss, element);
	    }
	}
	for (y=0; y<mpar_value; y++)
	{ 
	    if (qa.validate_parameter(pMparVars[y]))
	    {
		CedarReadParcods afx;
		string element = (string)afx.get_PCSFCT(abs(pMparVars[y]));// + string(" ") + (string) afx.get_PCULBL(pMparVars[y]);
		print_blocked(oss, element);
	    }
	}
	oss<<endl;

	print_blocked(oss, "N/A");
	print_blocked(oss, "N/A");
	print_blocked(oss, "yr");
	print_blocked(oss, "mmdd");
	print_blocked(oss, "hhmm");
	print_blocked(oss, "s");
	print_blocked(oss, "yr");
	print_blocked(oss, "mmdd");
	print_blocked(oss, "hhmm");
	print_blocked(oss, "s");
	print_blocked(oss, " ");

	for (w=0; w<jpar_value; w++)
	{ 
	    if (qa.validate_parameter(pJparVars[w]))
	    {
		CedarReadParcods afx;
		string element = (string) afx.get_PCULBL(abs(pJparVars[w]));
		print_blocked(oss, element);
	    }
	}
	for (y=0; y<mpar_value; y++)
	{ 
	    if (qa.validate_parameter(pMparVars[y]))
	    {
		CedarReadParcods afx;
		string element = (string) afx.get_PCULBL(abs(pMparVars[y]));
		print_blocked(oss, element);
	    }
	}
	oss<<endl;

	print_blocked(oss, dr.get_record_kind_instrument());
	print_blocked(oss, dr.get_record_kind_data());
	print_blocked(oss, bdate.get_year());
	print_blocked(oss, bdate.get_month_day());
	print_blocked(oss, bdate.get_hour_min());
	print_blocked(oss, bdate.get_second_centisecond());
	print_blocked(oss, edate.get_year());
	print_blocked(oss, edate.get_month_day());
	print_blocked(oss, edate.get_hour_min());
	print_blocked(oss, edate.get_second_centisecond());
	print_blocked(oss, dr.get_nrows());
	for (w=0; w<jpar_value; w++)
	{ 
	    if (qa.validate_parameter(pJparVars[w]))
		print_blocked(oss, pJparVars[w]);
	}
	for (y=0; y<mpar_value;y++)
	{
	    if (qa.validate_parameter(pMparVars[y]))
		print_blocked(oss, pMparVars[y]);
	}
	oss<<endl;

	int nrow_value=dr.get_nrows();

	short int *pJparData =new short int[jpar_value];
	if (!pJparData)
	{
	    throw bad_alloc();
	}
	dr.load_JPAR_data(pJparData);
	short int *pMparData=new short int[nrow_value*mpar_value];
	if (!pMparData)
	{
	    throw bad_alloc();
	}
	dr.load_MPAR_data(pMparData);

	CedarParameter pp ;
	for (int o=0; o<nrow_value; o++)
	{
	    bool print_row = true ;
	    if( qa.got_parameter_constraint() )
	    {
		for( z = 0; z < mpar_value; z++ )
		{
		    if( qa.validate_parameter( pMparVars[z] ) )
		    {
			pp = qa.get_parameter( pMparVars[z] ) ;
			if( !pp.validateValue( pMparData[z+(o*mpar_value)] ) )
			{
			    print_row = false ;
			}
		    }
		}
	    }
	    if( print_row )
	    {
		print_blocked(oss, dr.get_record_kind_instrument());
		print_blocked(oss, dr.get_record_kind_data());
		print_blocked(oss, bdate.get_year());
		print_blocked(oss, bdate.get_month_day());
		print_blocked(oss, bdate.get_hour_min());
		print_blocked(oss, bdate.get_second_centisecond());
		print_blocked(oss, edate.get_year());
		print_blocked(oss, edate.get_month_day());
		print_blocked(oss, edate.get_hour_min());
		print_blocked(oss, edate.get_second_centisecond());
		print_blocked(oss, dr.get_nrows());
		for (w=0; w<jpar_value; w++)
		{ 
		    if (qa.validate_parameter(pJparVars[w]))
			print_blocked(oss, pJparData[w]);
		}
		for (y=0; y<mpar_value;y++)
		{
		    if (qa.validate_parameter(pMparVars[y]))
			print_blocked(oss, pMparData[y+(o*mpar_value)]);
		}
		oss<<endl;
	    }
	}

	delete [] pJparVars;
	delete [] pMparVars;
	delete [] pJparData;
	delete [] pMparData;
	oss<<'\n'<<endl;

	oss<<'\0';
	char *p=0;
	p=oss.str();
	if (p) 
	{
	    cf.add_data(string(p));
	    delete p;
	}
    }
}

int cedar_read_flat(CedarFlat &cf, string filename, string query, string &error)
{
    CedarConstraintEvaluator qa;
    try
    {
	qa.parse(query.c_str());
    }
    catch (CedarException &ex)
    {
	cerr<<"Exception parsing\n";
	error=ex.get_description();
	return 0;
    }

    CedarFile file;
    try
    {
	file.open_file (filename.c_str());
	const CedarLogicalRecord *lr =file.get_first_logical_record();

	if(lr)
	{
	    if((lr->get_type()==1))
	    {
		send_flat_data(cf, *(CedarDataRecord*)lr,qa);
	    }
	    while (!file.end_dataset())
	    {
		lr=file.get_next_logical_record();
		if(lr)
		{
		    if((lr->get_type()==1))
		    {
			send_flat_data(cf, *(CedarDataRecord*)lr,qa);
		    }
		}
	    }
	}
	else 
	{
	    error="Failure reading data, corrupted file or not a cbf file.\n";
	    return false;
	}
    }
    catch (CedarException &cedarex)
    {
	error="The requested dataset produces the following exception ";
	error+=cedarex.get_description() + (string)"\n";
	return 0;
    }
    catch (bad_alloc::bad_alloc)
    {
	error="There has been a memory allocation error.\n";
	return 0;
    }
    catch (...)
    {
	error="There has been an undefined exception while executing the request.\n";
	return 0;
    }

    return 1;
}
 
// $Log: cedar_read_flat.cc,v $
// Revision 1.2  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
