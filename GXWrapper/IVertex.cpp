#include "IVertex.h"
using namespace Break::GXWrapper;
IVertex::IVertex(){

}
IVertex::~IVertex(){

}
VertexDeclaration IVertex::getVertexDeclaration(){
	return VertexDeclaration(0,NULL,0);
}