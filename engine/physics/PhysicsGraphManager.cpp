/*
Copyright (c) 2013 Daniele Bartolini, Michele Rossi
Copyright (c) 2012 Daniele Bartolini, Simone Boscaratto

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#include "PhysicsGraphManager.h"
#include "PhysicsGraph.h"

namespace crown
{

//-----------------------------------------------------------------------------
PhysicsGraphManager::PhysicsGraphManager()
	: m_graphs(default_allocator())
{

}

//-----------------------------------------------------------------------------
PhysicsGraphManager::~PhysicsGraphManager()
{
}

//-----------------------------------------------------------------------------
PhysicsGraph* PhysicsGraphManager::create_physics_graph()
{
	uint32_t index = m_graphs.size();
	PhysicsGraph* pg = CE_NEW(default_allocator(), PhysicsGraph)(index);
	m_graphs.push_back(pg);
	return pg;
}

//-----------------------------------------------------------------------------
void PhysicsGraphManager::destroy_physics_graph(PhysicsGraph* pg)
{
	CE_ASSERT_NOT_NULL(pg);

	m_graphs[pg->m_index] = m_graphs[m_graphs.size() - 1];
	m_graphs.pop_back();

	CE_DELETE(default_allocator(), pg);
}

//-----------------------------------------------------------------------------
void PhysicsGraphManager::update()
{
	for (uint32_t i = 0; i < m_graphs.size(); i++)
	{
		m_graphs[i]->update();
	}
}

};