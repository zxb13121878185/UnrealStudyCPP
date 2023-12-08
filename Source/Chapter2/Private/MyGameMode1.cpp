// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode1.h"

AMyGameMode1::AMyGameMode1()
{
	DefaultPawnClass = AMyPawn1::StaticClass();
	PlayerControllerClass = AMyPlayerController1::StaticClass();
	GameStateClass = AMyGameState1::StaticClass();
	PlayerStateClass = AMyPlayerState1::StaticClass();
	HUDClass = AMyHUD1::StaticClass();
}

void AMyGameMode1::BeginPlay()
{
	Super::BeginPlay();

	//打印到输出日志窗口
	//LogTemp临时日志记录类别名称，Warning日志记录的级别，TEXT是要打印文本的内容，内容如果为中文会乱码
	//日志记录的级别有三种从大至小分别为：Error（红色）、Warning（黄色）、Display（白色）
	//UE_LOG(LogTemp, Warning, TEXT("This is a Warning Info!"));
	UE_LOG(LogTemp, Warning, TEXT("%d"), 10);//打印整形
	UE_LOG(LogTemp, Warning, TEXT("%f"), 0.1f);//打印浮点数
	UE_LOG(LogTemp, Warning, TEXT("%d"), false);//打印Bool类型
	UE_LOG(LogTemp, Warning, TEXT("%c"), 'A');//打印Char类型

	FString tempStr2 = "测试打印";
	UE_LOG(LogTemp, Warning, TEXT("%s"), *tempStr2);//打印String类型


	FVector tempVec = FVector(1, 2, 3);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *tempVec.ToString());//打印向量
	//打印到屏幕上：-1是默认值，5.0是显示在屏幕上的时间，文本内容为中文会乱码
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("This is a ScreenDebugInfo"));

#pragma region Type cast

	//创建一个Fstring
	FString MyString = TEXT("I am string");
	//Fstring 转换成Fname
	FName MyName = FName(*MyString);
	//Fstring转换成FText
	FText MyText = FText::FromString(MyString);

	//Fname转换成Fstring
	MyString = MyName.ToString();
	//FName转换成FText
	FText text1 = FText::FromName(MyName);
	//FText转化成FString
	FString strFromText = text1.ToString();
	//注意这里Ftext不能直接转化成FName，需要先转化成FString，然后再转化成FName

#pragma endregion

	/* 数组
	MyArray.Add(10);
	MyArray.Add(20);
	MyArray.Add(30);
	MyArray.AddUnique(20);//如果有相同元素不添加，反之则添加
	MyArray.AddUnique(40);

	PrintF();

	//删除
	MyArray.Remove(20);//移除所有等值的元素
	MyArray.RemoveSingle(10);//移除首个匹配的元素
	MyArray.RemoveAt(3);
	MyArray.Empty();//清空
	MyArray.Reset();//数量不变，所有元素的值为默认值
	//更改
	MyArray.Insert(60, 0);//在0号位置插入一个元素60

	int32& temp1 = MyArray[0];
	temp1 = 50;//修改该元素的值
	//查找
	MyArray.Contains(10);//查找我们数组是否包含了某个元素
	MyArray.Find(10);//正向查找的第一个匹配值
	MyArray.FindLast(10);//从反向开始查找到第一个匹配的元素
	*/

	/* 容器
	//TMap容器时一种键值对容器，里面的数据都是成对出现的（key,value),Key唯一
	//增加内容
	MyMap.Emplace(0, 1);
	MyMap.Add(1, 2);//两个增加元素是一样的
	PrintMap();
	//删除
	MyMap.Remove(0);//参数为Key的值
	MyMap.Empty();
	//查找
	MyMap.Contains(1);//进行两次查找
	int32* isFind= MyMap.Find(6);//查找匹配的Key值是否存在，只进行一次查找，返回的是指针
	const int32* isFind= MyMap.FindKey(2);//反向查找，返回类型为指针
	//分别获取所有的keys和Values
	TArray<int32> TestKeys;
	TArray<int32> TestValues;
	MyMap.GenerateKeyArray(TestKeys);
	MyMap.GenerateValueArray(TestValues);
	*/

	/* TSet
	//TSet是快速容器类，通常用于在排序不重要的情况下存储唯一元素，和TMap不同它是将数组值作为键，而不是数据值和键值相互独立
	//TSet可以快速查找、添加、删除元素（恒定时间），它也是值类型，支持复制、析构函数操作以及其元素较强的所有权。
	MySet.Add(TEXT("Banana"));
	MySet.Add(TEXT("Grapefruit"));
	MySet.Add(TEXT("Pineapple"));
	MySet.Emplace(TEXT("Orange"));//区别：Emplace可以避免在插入集合时创建的临时文件 .

	//合并元素
	TSet<FString> MySet2;
	MySet2.Add(TEXT("zhangSan"));
	MySet2.Add(TEXT("wangwu"));
	MySet2.Add(TEXT("zhaosi"));
	MySet.Append(MySet2);

	//移除
	MySet.Remove(TEXT("Banana"));//返回删除所有元素的数量，如果没有这个元素则返回0
	MySet.Empty();//清空元素会释放内存
	MySet.Reset();//清空元素但是会保存内存

	//查找元素
	MySet.Num();//查询集合中保存的元素数量
	bool isFind= MySet.Contains(TEXT("Banana"));//查询是否包含特定元素，找到为真否则为假
	FString* isFind2= MySet.Find(TEXT("Banana"));//返回的是指向元素数组的指针，如果映射不包含该键，则返回NUll

	//Array函数
	TArray<FString> FruitArray = MySet.Array();//函数会返回一个Tarry，其中填充了TSet中每一个元素的副本
	//排序
	TSet<FString> tempSet = { TEXT("a"),TEXT("aa"),TEXT("aaa"),TEXT("aaaa") };
	tempSet.Sort([](FString A, FString B) {return A.Len() > B.Len(); });//返回按字符长度的排序

	//运算符=
	TSet<FString>NewSet;
	NewSet = MySet;//将MySet里面的值赋值给NewSet

	//[]访问元素
	FSetElementId tempIndex = NewSet.Add(TEXT("from Index"));
	NewSet[tempIndex] = TEXT("From Two Index");

	//ReServe
	TSet<FString> tempSet2;
	tempSet2.Reserve(10);//预先分配内存，如输入的元素大于设定的个数，则会产生闲置内存（Slack）
	//Shrink
	for (int32 i = 0; i < 10; i++)
	{
		tempSet2.Add(FString::Printf(TEXT("NewSet %d"), i));//添加元素
	}
	for (size_t i = 0; i < 10; i+=2)
	{
		tempSet2.Remove(FSetElementId::FromInteger(i));
	}
	tempSet2.Shrink();//删除末端的空元素

	tempSet2.Compact();	//Compact将容器中所有空白闲置的元素集合到末尾等待一起删除,它会改变元素的原本顺序
	tempSet2.CompactStable();//它不会改变元素原本的顺序
	tempSet2.Shrink();

	PrintSet();
	*/

	varBool = false;
}

void AMyGameMode1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyGameMode1::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMyGameMode1::PrintF()
{
	//使用迭代器遍历数组
	for (auto It = MyArray.CreateConstIterator(); It; It++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d"), *It);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%d"), *It));
	}
}

void AMyGameMode1::PrintMap()
{
	for (auto& TestMap : MyMap)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Key:%d" "Value:%d"), TestMap.Key, TestMap.Value));
		UE_LOG(LogTemp, Warning, TEXT("key:%d value:%d"), TestMap.Key, TestMap.Value);
	}
}

void AMyGameMode1::PrintSet()
{
	for (auto& tempSet : MySet)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%s"), *tempSet));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *tempSet);
	}
}
