#ifndef TYPES_10_H
#define TYPES_10_H
enum product {
	SHAMPOO,
	TOILETPAPER,
	TOOTHPASTE,
};

enum unit {
	METER,
	MILLILITER,
};

enum month {
	JANUARY,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER,
};

struct date {
	enum month month;
	unsigned char date;
};

struct logentry {
	unsigned long amount;
	enum unit unit;
	enum product product;
};

struct perioduse {
	unsigned long amount[3];
};

enum weekday {
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
};

#endif
