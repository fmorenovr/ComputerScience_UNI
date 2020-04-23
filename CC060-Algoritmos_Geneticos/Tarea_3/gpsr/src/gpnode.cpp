#include <iostream>
#include "gpnode.h"

using namespace std;

GPNode::GPNode() {
	this->data = 0;
	this->nodetype = "constant";
	this->arityMin1 = -1;
}

GPNode::GPNode(int data, string nodetype, int arityMin1) {
	this->data = data;
	this->nodetype = nodetype;
	this->arityMin1 = arityMin1;
}

GPNode::GPNode(const GPNode &other) {
	this->data = other.getData();
	this->nodetype = other.getType();
	this->arityMin1 = other.getArity();
}

GPNode::~GPNode() {
	this->nodetype.erase();
}

void GPNode::operator=(const GPNode &rhs) {
	this->data = rhs.getData();
	this->nodetype = rhs.getType();
	this->arityMin1 = rhs.getArity();
}

int GPNode::getData() const {
	return this->data;
}

string GPNode::getType() const {
	return this->nodetype;
}

int GPNode::getArity() const {
	return this->arityMin1;
}

void GPNode::setData(int data) {
	this->data = data;
}

void GPNode::setType(string nodetype) {
	this->nodetype = nodetype;
}

void GPNode::setArity(int arity) {
	this->arityMin1 = arity;
}

ostream& operator<<(ostream& os, GPNode &gpnode) {
	os << gpnode.getType();
	return os;
}
