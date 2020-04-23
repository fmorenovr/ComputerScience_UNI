#ifndef GPNODE_H
#define GPNODE_H

#include <string>

class GPNode {

	public:
		GPNode();
		GPNode(int data, std::string nodetype, int arityMin1);
		GPNode(const GPNode &other);
		~GPNode();
		void operator=(const GPNode &rhs);
		int getData() const;
		std::string getType() const;
		int getArity() const ;
		void setData(int data);
		void setType(std::string nodetype);
		void setArity(int arity);

	private:
		int data;
		std::string nodetype;
		int arityMin1;

		friend std::ostream& operator<<(std::ostream& os, GPNode& gpnode);

};
#endif
