#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <ctime>
#include <iostream>
#include <iterator>
#define Max 1000
#define zero '0' 

using namespace std;

typedef struct ZZ {
	long long number = 0;
};


// tao 1 lop BigInt
// co thuoc tinh la mang kieu long number dung de bieu dien so nguyen lon
// co ki kieu char sign de xac dinh so am hay duong
// neu am sign = '-' con am '0'
// cac phuong thuc 
// cong(add),tru(sub),

class BigInt {
	public:
		
		vector<ZZ> zz;
		char sign;
		
		BigInt() {
			this->sign = '0';
		}
		BigInt(char *BigNumber) {
			this->sign = '0';
			this->setBigInt(BigNumber);
		}
		~BigInt() {
			zz.clear();
			this->sign = 0;
		}
		void setBigInt(const char *b);
		vector<ZZ> getBigInt() {
			return this->zz;
		}
		void outPut(); 					// dua so ra man hinh
		int length(); 					// tra ve do dai cua mang so zz;
		void dao_so(); 		    		// dao mang so zz
		BigInt abs();					// lay gia tri tuyet doi cua so BigInt
		BigInt covert(long a);
		BigInt Mul_Native(BigInt y);
		void drop_zero(int n);
		void addition_zero(int n);
		int compareBigInt(BigInt b);
		BigInt add(BigInt b);
		BigInt sub(BigInt b);
		BigInt mul(BigInt b);
		BigInt mul(long b);
		BigInt div(BigInt b);
		BigInt mod(BigInt b);
		BigInt &operator<<=(int n);	
		friend BigInt operator + (BigInt a,BigInt b);
		friend BigInt operator - (BigInt a,BigInt b);
		friend BigInt operator * (BigInt a,BigInt b);
		friend BigInt operator * (BigInt a,long b);
		friend BigInt operator / (BigInt a,BigInt b);
		friend BigInt operator % (BigInt a,BigInt b);
		friend bool operator > (BigInt a,BigInt b);
		friend bool operator >= (BigInt a,BigInt b);
		friend bool operator < (BigInt a,BigInt b);
		friend bool operator <= (BigInt a,BigInt b);
		friend bool operator == (BigInt a,BigInt b);
		friend bool operator != (BigInt a,BigInt b);
};

//BigInt module;

//void setMod(char* mod) {
//	module.setBigInt(mod);
//	return;
//}
//
//BigInt getMod() {
//	return module;
//}
void BigInt::setBigInt(const char* b) {
	if(b == NULL) return;
	int i=0,k=0,m =0,n;
	if(b[0] == '-'){
		this->sign = '-';
		i = 1;
	}
	n = i;
	char c[9];
	while(b[i]!=NULL) i++;
	for(int j = i-1;j>=n;j--){
		k++;
		ZZ a;
		if(k%9 == 0) {
			m = j;
			for(int v =0;v < k;v++) {
				c[v] = b[m];
				 m++;
			}
			a.number = atol(c);
			this->zz.push_back(a);
			m = j;
			k =0;
		}else if(j == n) {
			m =j;
			for(int v =0;v < k;v++) {
				c[v] = b[m];
				m++;
			}
			c[k] = NULL;
			a.number = atol(c);
	//		printf("\n%ld \n%d",a.number,m);
			this->zz.push_back(a);
		}
	}
}

// tra ve do dai cua chuoi so

int BigInt::length() {
	int n =0;
	n = this->zz.size();
	return n;
}

BigInt BigInt::covert(long a) {
	ZZ b;
	b.number = a;
	this->zz.clear();
	this->zz.push_back(b);
	if(a < 0) this->sign = '-';
	else this->sign = '0'; 
	return *this;
}

void BigInt::outPut() {
	if(this->sign == '-') {
		printf("%c",this->sign);
	}
	for(int i =this->length() -1;i>=0;i--) {
		printf("%ld",this->zz[i]);
	}
}

BigInt BigInt::abs() {
	BigInt b;
	b = *this;
	if(this->sign == '-'){
		b.sign = '0';
	}
	return b;
}

int BigInt::compareBigInt(BigInt b) {
	if(b.sign == '-' && this->sign == '-') {
		if(this->length() > b.length()) {
			return -1;
		}
		else if(this->length() < b.length()) return 1;
		else {
			for(int i = this->length()-1;i>=0;i--) {
				if(this->zz[i].number > b.zz[i].number) {
					return -1;
				} else if(this->zz[i].number < b.zz[i].number) {
					return 1;
				}
			}
		}
		return 0;
	}else if(b.sign != '-' && this->sign !='-') {
		if(this->length() > b.length()) return 1;
		else if(this->length() < b.length()) return -1;
		else{
			for(int i = this->length()-1;i>=0;i--) {
			  if(this->zz[i].number > b.zz[i].number) {
					return 1;
				}else if(this->zz[i].number < b.zz[i].number){
	//				printf("\n%ld \n%ld",this->zz[i].number,b.zz[i].number);
					return -1;
				}
			}
			return 0;
		}
	}else if(b.sign == '-' && this->sign !='-') {
		return 1;
	}else return -1;
}

bool operator > (BigInt a,BigInt b) {
	
	if(a.compareBigInt(b) > 0) 
		return true;
	else false;
	
}

bool operator >= (BigInt a,BigInt b) {
	
	if(a.compareBigInt(b) >= 0) 
		return true;
	else return false;
}

bool operator < (BigInt a,BigInt b) {
	
	if(a.compareBigInt(b) < 0) 
		return true;
	else return false;
	
}

bool operator <= (BigInt a,BigInt b) {
	
	if(a.compareBigInt(b) <= 0) 
		return true;
	else return false;
	
}

bool operator == (BigInt a,BigInt b) {
	
	if(a.compareBigInt(b) == 0) 
		return true;
	else return false;
	
}

bool operator != (BigInt a,BigInt b) {
	
	if(a.compareBigInt(b) != 0)
		return true;
	else return false;
	
}

inline long value_add(long a,long b,long &carry) {
	long long temp = a + b + carry;
	carry = temp/((long)1000000000);
	return (long)(temp%1000000000);
}


BigInt BigInt::add(BigInt b) {
	BigInt e;
	ZZ a;
	int i = 0;long carry = 0;
	if((this->sign == '-' && b.sign == '-')
				|| (this->sign != '-' && b.sign != '-')) {
		while(i < this->zz.size()  && i < b.zz.size()) {
			a.number = value_add(this->zz[i].number,b.zz[i].number,carry);
			e.zz.push_back(a);
			i++;
		}
		if(i<this->zz.size()) {
			while(i < this->zz.size()){
				a.number = value_add(this->zz[i].number,0,carry);
				e.zz.push_back(a);
				i++;
			}
		}
		if( i< b.zz.size()) {

			while(i< b.zz.size()) {
				a.number = value_add(b.zz[i].number,0,carry);
				e.zz.push_back(a);
				i++;
			}
		}
		if(carry) {
			a.number = carry;
			e.zz.push_back(a);
			i++;
		}
		if(this->sign == '-') {
			e.sign = '-';
		}
		return e;
	}else {
		
		e = this->abs().sub(b.abs());
		if(this->sign == '-')
			if(this->abs().compareBigInt(b.abs()) == 1) {
				e.sign = '-';
			}else if(this->abs().compareBigInt(b.abs()) == -1) {
				e.sign = '0';
			}
	}
		return e;
}

BigInt operator + (BigInt a,BigInt b) {
	return a.add(b);	
}

inline long value_sub(long a,long b,long &carry) {
	long temp = (long)1000000000 + a - b - carry;
	carry = 1 - temp/((long)1000000000);
	return (long)(temp%1000000000);
}

inline BigInt BigInt::sub(BigInt b) {
	BigInt e;
	ZZ a;
	int i =0;long carry =0;
	if((this->sign == '-' && b.sign == '-') 
					|| (this->sign !='-' && b.sign != '-')) {
		if(this->abs().compareBigInt(b.abs()) >= 0) { // neu so thu 1 > so thu 2
			while(i < this->zz.size() && i < b.zz.size()) {
				a.number = value_sub(this->zz[i].number,b.zz[i].number,carry);
				e.zz.push_back(a);
				i++;
			}
			while(i < this->zz.size()) {
				a.number = value_sub(this->zz[i].number,0,carry);
				e.zz.push_back(a);
				i++;
			}
			while(e.zz[--i].number == 0 && i > 0) {
				e.zz.pop_back();
			}
			if(this->sign == '-') {
				e.sign = '-';
			}
		}else if(this->abs().compareBigInt(b.abs()) == -1) {
			while(i < this->zz.size() && i < b.zz.size()) {
				a.number = value_sub(b.zz[i].number,this->zz[i].number,carry);
				e.zz.push_back(a);
				i++;
			}
			while(i < b.zz.size()) {
				a.number = value_sub(b.zz[i].number,0,carry);
				e.zz.push_back(a);
				i++;
			}
			while(e.zz[--i].number == 0 && i > 0) {
				e.zz.pop_back();
			}
			if(b.sign != '-') {
				e.sign = '-';
			}else {
				e.sign = '0';
			}
		}
	}else { // neu 2 so ko cung dau
		e = this->abs().add(b.abs());
		if(this->sign == '-') {
			e.sign = '-';
		}else {
			e.sign = '0';
		}
	}
	return e;
}

BigInt operator - (BigInt a,BigInt b) {
	return a.sub(b);
}

inline long value_mul(long a,long b,long &carry) {
	long long temp = (long long)a*b + carry;
	carry = temp/((long)1000000000);
	return (long)(temp%1000000000);
}

BigInt BigInt::mul(long b) {
	int i =0;
	long carry = 0;
	ZZ a;
	BigInt f;
	while(i < this->length()) {
		a.number = value_mul(this->zz[i].number,b,carry);
		f.zz.push_back(a);
		i++;
	}
	if(carry) {
		a.number = carry;
		f.zz.push_back(a);
	}
	return f;

}


inline void BigInt::drop_zero(int n) {
	this->zz.erase(this->zz.begin(),this->zz.begin()+n);
}

inline void BigInt::addition_zero(int n) {
	ZZ a;
	this->zz.insert(this->zz.begin(),n,a);
}

BigInt BigInt::Mul_Native(BigInt y) {
	
	BigInt e;
	ZZ g;
	
	int j =0;
		while(j < y.length()) {
			BigInt f;
			int i = 0; long carry = 0;
			while(i< this->length()) {
				g.number = value_mul(this->zz[i].number,y.zz[j].number,carry);
				f.zz.push_back(g);
				i++;
			}
			if(carry) {
				g.number = carry;
				f.zz.push_back(g);
				i++;
			}
			if(j==0) e = f;
			else {
				f.addition_zero(j);
				e = e.add(f);
			}
			j++;
		}
		return e;
		
}

BigInt & BigInt::operator<<=(int n) {
	this->addition_zero(n);
	return *this;
}

void split(BigInt x,BigInt y,BigInt &a,BigInt &b,BigInt &c,BigInt &d,int m) {
	
	int size1 = x.zz.size();
	
	b.zz.resize(m);
	a.zz.resize(size1- m);
	
	d.zz.resize(m);
	c.zz.resize(size1- m);
	
	copy(x.zz.begin(),x.zz.begin()+m,b.zz.begin());
	copy(x.zz.begin()+m,x.zz.end(),a.zz.begin());
	
	copy(y.zz.begin(),y.zz.begin()+m,d.zz.begin());
	copy(y.zz.begin()+m,y.zz.end(),c.zz.begin());
	
}

// thuat toan nhan Karatsuba

BigInt Karatsuba(BigInt x,BigInt y,int n) {
	BigInt e;
	if(n < 100) {
		e = x.Mul_Native(y); 
		return e;
	}
	BigInt a,b,c,d,U,V,W;
		split(x,y,a,b,c,d,n/2);
		U = Karatsuba(a,c,n/2);
		V = Karatsuba(b,d,n/2);
		W = Karatsuba(a + b,c + d,n/2) - U - V;
		W.addition_zero(n/2);
		
		if(n%2 == 0){
			U.addition_zero(n);
			e = U + W + V;
		}else{
			U.addition_zero(n-1);
			e = U + V + W;
		}
		
		return e;
}

BigInt BigInt::mul(BigInt b) {
	BigInt e;
	int n;
	if((this->zz[this->length() -1].number == 0) && (b.zz[b.length()-1].number == 0)) {
		return e;
	}
	if(this->length() < 30 || b.length() < 30) {
		e = this->Mul_Native(b);
	}else {
		if(this->length() > b.length()) {
			n = this->length() - b.length();
			b.addition_zero(n);
			e = Karatsuba(*this,b,this->length());
			e.drop_zero(n);
		} else if(this->length() < b.length()) {
			n = b.length() - this->length();
			this->addition_zero(n);
			e = Karatsuba(*this,b,b.length());
			e.drop_zero(n); 
		}else {
			e = Karatsuba(*this,b,b.length());
		}
	}
	
	if((this->sign == '-' && b.sign == '0') 
				|| (this->sign == '0' && b.sign == '-')) {
			e.sign = '-';
		}
	return e;
}

BigInt operator * (BigInt a,BigInt b) {
	return a.mul(b);
}

BigInt operator * (BigInt a,long b) {
	return a.mul(b);
}

BigInt r;

BigInt BigInt::div(BigInt b) {
	BigInt q,p,temp,g;
	if(b.compareBigInt(temp.covert(0)) == 0) return temp; 
	temp = this->abs();
	g = b.abs();
	q.covert(1);
	
	if(temp.compareBigInt(g) == 0) {
		r.covert(0);
		return q.covert(1);
	}else if(temp.compareBigInt(g) < 0) {
		r = temp;
		return q.covert(0);
	}
	BigInt temp1;
	while(g.compareBigInt(temp) <= 0) {
		temp1 = g.mul(2);
		if(temp1.compareBigInt(temp) <= 0) {
			g = temp1;
			q = q.mul(2);
		}else {
			break;
		}	
	}
	
	q = q.add(temp.sub(g).div(b));
	return q;
}

BigInt operator / (BigInt a,BigInt b) {
	
	BigInt div = a.div(b);
	if(a.sign != b.sign) {	
		div.sign = '-'; 
	}else {
		div.sign = '0';
	}
	return div;
}

BigInt BigInt::mod(BigInt b) {
	div(b);
	return r;
}

BigInt operator % (BigInt a,BigInt b) {
	
	BigInt mod = a.mod(b);
	BigInt Zero("0");
	if(mod.compareBigInt(Zero) == 0) return Zero;
	
	if(a.sign != b.sign) {
		if(a.sign == '-')  mod.sign = '-';
		else mod.sign = '0';
	}else {
		if(a.sign == '-') mod.sign = '-';
		else mod.sign = '0';
	}
	return mod;
}

BigInt extended_gcd(BigInt a,BigInt b) {
	
	BigInt s,t,r,old_s,old_t,old_r,temp,temp1;
	s.covert(0);
	t.covert(1);
	r = b;
	old_s.covert(1);
	old_t.covert(0);
	old_r = a;
	
	while(r.compareBigInt(temp.covert(0)) != 0) {
		
		BigInt quotient = old_r.div(r);
		temp1 = old_r;
		old_r = r;
		r = temp1.sub(quotient.mul(r));
		temp1 = old_s;
		old_s = s;
		s = temp1.sub(quotient.mul(s));
		temp1 = old_t;
		old_t = t;
		t = temp1.sub(quotient.mul(t));
	}
	return old_r;
}


BigInt Inverse(BigInt a,BigInt n) {
	
	BigInt a1;
	BigInt Zero("0");
	BigInt One("1");
	BigInt t("0");
	BigInt newt("1");	
	BigInt r = n;
	BigInt newr = a;
	BigInt temp;
	
	while(newr.compareBigInt(Zero) != 0) {
		
		BigInt quotient = r.div(newr);
		temp = t;
		t = newt;
		newt = temp.sub(quotient.mul(newt));
		temp = r;
		r = newr;
		newr = temp.sub(quotient.mul(newr));
	} 
	
	if(r.compareBigInt(One) > 0) {
		printf("a is not invertible");
		return a1;
	}
	
	if(t.compareBigInt(Zero) < 0) t = t.add(n);
	return t;
}


BigInt Fast_exp(BigInt base,BigInt exp) {
	
	BigInt temp,temp1,temp3;
	temp.covert(1);
	temp1.covert(2);
	temp3.covert(0);
	if(exp.compareBigInt(temp3) == 0) return temp;
	if(exp.compareBigInt(temp) == 0) {
		return base;
	}else {
		if((exp.mod(temp1)).compareBigInt(temp3) == 0) {
			BigInt temp4 =  Fast_exp(base,exp.div(temp1));
			return temp4.mul(temp4);
		}else {
			BigInt temp4 = Fast_exp(base,exp.sub(temp).div(temp1));
			return temp4.mul(temp4).mul(base);
		}
	}
}

BigInt modExp(BigInt base,BigInt exp,BigInt &n) {
	
	BigInt Zero("0");
	BigInt One("1");
	BigInt Two("2");
	BigInt result;
	// Get base cases out of the way.
	if(exp.compareBigInt(Zero) == 0) return One;
	if(exp.compareBigInt(One) == 0) return base.mod(n);
	
	// Here is where we get our key savings.
	if(exp.mod(Two).compareBigInt(Zero) == 0) {
		
		// Just solve for the square root of the answer.
		BigInt ans = modExp(base,exp.div(Two),n);
		result = ans.mul(ans);
		if(result >= n) {
			return	result.mod(n);
		}
		// Save yourself a great deal of work by REUSING the
		// result of the square root, so to speak.
		return result;
	}else {
		BigInt ans = modExp(base,exp.sub(One).div(Two),n);
		result = ans.mul(ans).mul(base);
		if(result >= n) {
			return result.mod(n);
		}
		return result;
	}
	
}

/*
BigInt modExp1(BigInt base,BigInt exp,BigInt n) {

	BigInt Zero("0");
	BigInt One("1");
	BigInt Two("2");
	BigInt result("1");
	if(exp.compareBigInt(Zero) == 0) return One;
	if(exp.compareBigInt(One) == 0) return base.mod(n);
	
	while(exp > 0) {
		result = result.mul(base).mod(n);
		exp = exp - One;
	}
	
	return result;

}

*/


// Multiplication modular

BigInt mul_modular(BigInt a,BigInt b,BigInt modular) {
	
	return a.mul(b).mod(modular); 
	
}

BigInt add_modular(BigInt a,BigInt b,BigInt modular) {
	return (a+b).mod(modular);
}

BigInt sub_modular(BigInt a,BigInt b,BigInt modular) {
	if(a >= b) return ((a-b).mod(modular));
	else {
		return (a - b + modular);
	}
} 


BigInt div_modular(BigInt a,BigInt b,BigInt modular) {
	return (a.div(b)).mod(modular);
}


// Montgomery reduction

BigInt REDC(BigInt R,BigInt N,BigInt N1,BigInt T) {
	
	BigInt m = ((T.mod(R)).mul(N1)).mod(R);
	BigInt t = (T.add(m.mul(N))).div(R);
	
	if(t >= N) {
		return (t - N);
	}else {
		return t;
	}
	
}

// MultiPrecisionREDC 

//BigInt Mul_REDC(BigInt N,BigInt R,BigInt N1,BigInt T) {
	
	
	
//}
