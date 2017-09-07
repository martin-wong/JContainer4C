#include "ctreemap.h"



c_boolean _ctreemap_isRed(cTreeMapNode * node);
int32_t _ctreemap_size(cTreeMapNode * node);
cTreeMapNode * _ctreemap_newNode(void * key, void * value, int32_t n, enum Color color);
int32_t _ctreemap_size(cTreeMapNode * node);
void _ctreemap_flipColors(cTreeMapNode * node);
cTreeMapNode * _ctreemap_rotateLeft(cTreeMapNode * node);
cTreeMapNode * _ctreemap_rotateRight(cTreeMapNode * node);
cTreeMapNode * _ctreemap_putVal(cTreeMap * map, cTreeMapNode * node, void * key, void * value);


cTreeMap * ctreemap_create(uint32_t(*c_equals)(void * this, void *another), 
	int32_t(*c_compareTo)(void * this, void *another), int32_t(*c_hashCode)(void *elem), 
	void *(*c_copy)(void *elem), void(*c_destory)(void *elem), void(*c_destoryValue)(valueType *value)){
	
	cTreeMap * p = (cTreeMap *)malloc(sizeof(cTreeMap));
	if (!p) 
		return NULL;
	cMetadata *  metadata_p = (cMetadata *)malloc(sizeof(cMetadata));
	if (!metadata_p) {
		free(p);
		return NULL;
	}
	p->metaData = metadata_p;
	metadata_p->equals = c_equals;
	metadata_p->compareTo = c_compareTo;
	metadata_p->hashCode = c_hashCode;
	metadata_p->copy = c_copy;
	metadata_p->destory = c_destory;
	metadata_p->destoryValue = c_destoryValue;

	p->root = NULL;

	p->put = ctreemap_put;
	p->size = ctreemap_size;

	return p;
}

c_boolean ctreemap_put(cTreeMap * map, void * key, void * value) {
	cTreeMapNode * root = _ctreemap_putVal(map,map->root,key,value);
	if (!root)
		return c_FALSE; //插入失败
	map->root = root;
	root->color = BLACK; //根节点保证为黑色
}

//从node这颗树中插入键值对 返回数的根节点
cTreeMapNode * _ctreemap_putVal(cTreeMap * map, cTreeMapNode * node , void * key ,void * value) {
	
	if (!node)
		return _ctreemap_newNode(key, value, 1, RED);//新插入的一定是红节点
	int32_t cmp = map->metaData->compareTo(key,node->key);
	if (cmp < 0) {
		cTreeMapNode  * n = _ctreemap_putVal(map, node->left, key, value); //小于当前节点 递归调用左子树
		if (!n)
			return NULL;
		node->left = n;
	}
	else if (cmp > 0) {
		cTreeMapNode  * n = _ctreemap_putVal(map, node->right, key, value); //小于当前节点 递归调用左子树
		if (!n)
			return NULL;
		node->right = n;
	}
	else 
	   { map->metaData->destoryValue(node->value); node->value = value; } //覆盖

	//下面三步对树进行修复 注意顺序绝对不能颠倒
	if (!_ctreemap_isRed(node->left) && _ctreemap_isRed(node->right))
		node = _ctreemap_rotateLeft(node);
	if (_ctreemap_isRed(node->left) && _ctreemap_isRed(node->left->left))
		node = _ctreemap_rotateRight(node);
	if (_ctreemap_isRed(node->left) && _ctreemap_isRed(node->right))
		_ctreemap_flipColors(node);

	node->n = _ctreemap_size(node->left) + _ctreemap_size(node->right) + 1;
	return node;
}

int32_t ctreemap_size(cTreeMap * map) {
	if (!map)
		return 0;
	return map->root == NULL ? 0 : map->root->n;
}

//判断节点是否是红节点 注意NULL节点为黑节点
c_boolean _ctreemap_isRed(cTreeMapNode * node) {
	if (node == NULL)
		return c_FALSE;
	if (node->color == RED)
		return c_TRUE;
	return c_FALSE;
}

//创建一个节点
cTreeMapNode * _ctreemap_newNode(void * key, void * value, int32_t n, enum Color color ) {
	cTreeMapNode * p = (cTreeMapNode *)malloc(sizeof(cTreeMapNode));
	if (!p)
		return NULL;
	p->key = key;
	p->value = value;
	p->left = NULL;
	p->right = NULL;
	p->n = n;
	p->color = color;
	return p;
}

//返回节点的子节点数
int32_t _ctreemap_size(cTreeMapNode * node) {
	if (!node) return 0;
	return node->n;
}

//node节点的2个子节点都是红节点 要反转颜色
void _ctreemap_flipColors(cTreeMapNode * node) {
	node->color = RED;
	node->left->color = BLACK;
	node->right->color = BLACK;
}

//node节点的左子节点是红节点 右旋 使红节点出现在右侧
cTreeMapNode * _ctreemap_rotateRight(cTreeMapNode * node) {
	cTreeMapNode * x = node->left;
	node->left = x->right;
	x->right = node;
	x->color = node->color;
	node->color = RED;
	x->n = node->n;
	node->n = _ctreemap_size(node->left) + _ctreemap_size(node->right) + 1;
	return x; //现在，x就是原来node的位置 且x的左子节点是node
}

//node节点的右子节点是红节点 左旋 使红节点出现在左侧 
cTreeMapNode * _ctreemap_rotateLeft(cTreeMapNode * node) {
	cTreeMapNode * x = node->right;
	node->right = x->left;
	x->left = node;
	x->color = node->color;
	node->color = RED;
	x->n = node->n;
	node->n = _ctreemap_size(node->left) + _ctreemap_size(node->right) + 1;
	return x; //现在，x就是原来node的位置 且x的左子节点是node
}
