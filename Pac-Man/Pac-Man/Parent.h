#ifndef PARENT_H

class Parent {
public:
	Parent() {}
	virtual ~Parent() = 0;

	virtual void draw() = 0;
	virtual bool contains(const Parent*) = 0;
	virtual bool contains(const float, const float) = 0;
};

#endif // !PARENT_H
