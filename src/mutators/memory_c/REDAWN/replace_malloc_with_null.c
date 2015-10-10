/*
Milu v3.0 - A Higher Order Mutation Testing Tool

Copyright (c) 2015, Fan Wu
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the University College London nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "Mutator.h"
#include "ASTNodeUtil.h"

static gboolean mutator_milu_replace_malloc_with_null_node_checking(ASTNode *);
static gboolean mutator_milu_replace_malloc_with_null_clean(ASTNode * node, gint type);
static gboolean mutator_milu_replace_malloc_with_null_mutate(ASTNode * node, gint type);


Mutator * mutator_milu_replace_malloc_with_null()
{
	Mutator * mut = mutator_new("(Memory)Replace malloc() with NULL", "");
	mut->node_checking = & mutator_milu_replace_malloc_with_null_node_checking;
	mut->mutate = & mutator_milu_replace_malloc_with_null_mutate;
	mut->clean = & mutator_milu_replace_malloc_with_null_clean;
	mut->size = 1;
	return mut;
}


static gboolean mutator_milu_replace_malloc_with_null_node_checking(ASTNode * node)
{
	return is_ASTNode_malloc_call(node);
}

static gboolean mutator_milu_replace_malloc_with_null_mutate(ASTNode * node, gint type)
{
	ASTNode * replace;
	switch(type)
	{
		case 1:
			replace=ASTNode_new_null_pointer_node();
			replace_subtree_with(node, replace);
			replace->ext[0]=node;
			return TRUE;

		default:
			break;
	}

	return FALSE;
}

static gboolean mutator_milu_replace_malloc_with_null_clean(ASTNode * node, gint type)
{
	ASTNode* ori=(ASTNode*)(node->ext[0]);
	replace_subtree_with(node, ori);
	node->ext[0]=0;
	// TODO free the mutation tree
	printf("%s\n", node->text);
	return TRUE;
}