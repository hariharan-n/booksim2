// $Id$

/*
Copyright (c) 2007-2009, Trustees of The Leland Stanford Junior University
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list
of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this 
list of conditions and the following disclaimer in the documentation and/or 
other materials provided with the distribution.
Neither the name of the Stanford University nor the names of its contributors 
may be used to endorse or promote products derived from this software without 
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
*/

#include <sstream>

#include "globals.hpp"
#include "booksim.hpp"
#include "buffer.hpp"

Buffer::Buffer( const Configuration& config, int outputs, 
		Module *parent, const string& name ) :
  Module( parent, name )
{
  int num_vcs = config.GetInt( "num_vcs" );

  _vc.resize(num_vcs);

  for(int i = 0; i < num_vcs; ++i) {
    ostringstream vc_name;
    vc_name << "vc_" << i;
    _vc[i] = new VC(config, outputs, this, vc_name.str( ) );
  }
}

bool Buffer::AddFlit( int vc, Flit *f )
{
  return _vc[vc]->AddFlit(f);
}

Flit *Buffer::RemoveFlit( int vc )
{
  return _vc[vc]->RemoveFlit( );
}

bool Buffer::Empty( int vc ) const
{
  return _vc[vc]->Empty( );
}

bool Buffer::Full( int vc ) const
{
  return _vc[vc]->Full( );
}

void Buffer::Display( ) const
{
  for(vector<VC*>::const_iterator i = _vc.begin(); i != _vc.end(); ++i) {
    (*i)->Display();
  }
}