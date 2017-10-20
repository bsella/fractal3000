#include "palette.h"

/*Uint32 = [........][..RED...][.GREEN..][..BLUE..]*/

struct paletteColor{
	Uint32 clr;
	double index;
	struct paletteColor *next;
};

static void getRGB(Uint32 color, Uint8*r, Uint8*g, Uint8*b){
	*b=color;
	color>>=8;
	*g=color;
	color>>=8;
	*r=color;
}

static Uint32 makeRGB(Uint8 r, Uint8 g, Uint8 b){
	Uint32 c=r;
	c<<=8; c|=g;
	c<<=8; c|=b;
	return c;
}

Palette* pltInit(){
	Palette* plt=malloc(sizeof(Palette));
	plt->first=NULL;
	return plt;
}

int pltEmpty(Palette plt){
	return plt.first==NULL;
}

void pltAdd(Palette *p, Uint32 color, double i){
	if(i<0)i=0;
	if(i>1)i=1;
	struct paletteColor *new=malloc(sizeof(struct paletteColor));
	new->clr=color;
	new->index=i;
	new->next=NULL;
	if(pltEmpty(*p))
		p->first=new;
	else{
		if(p->first->index>i){
			new->next=p->first;
			p->first=new;
		}else{
			struct paletteColor *it=p->first;
			while(it->next!=NULL && it->next->index<i)
				it=it->next;
			new->next=it->next;
			it->next=new;
		}
	}
}

static Uint32 average(struct paletteColor c1, struct paletteColor c2, double i){
	i=(i-c1.index)/(c2.index-c1.index);
	Uint8 r1,g1,b1, r2,g2,b2;
	getRGB(c1.clr,&r1,&g1,&b1);
	getRGB(c2.clr,&r2,&g2,&b2);
	return makeRGB(r2*i+(1.0-i)*r1
					,g2*i+(1.0-i)*g1
					,b2*i+(1.0-i)*b1);
}

Uint32 pltGet(Palette p, double i){
	if(pltEmpty(p)) return 0;
	if(i<0) return p.first->clr;
	struct paletteColor *it=p.first;
	while(it->next!=NULL && it->next->index<i)
		it=it->next;
	if(it->next==NULL)
		return it->clr;
	return average(*it, *(it->next), i);
}

static void freeFirst(Palette *p){
	struct paletteColor *f=p->first;
	p->first=p->first->next;
	free(f);
}

void pltFree(Palette *p){
	while(!pltEmpty(*p))
		freeFirst(p);
	free(p);
}