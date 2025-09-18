#pragma once

#include <objbase.h>
#include <vector>
#include <memory>
#include <comdef.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

enum EDatabaseIDX
{
	DATABASEID_NULL,
	DATABASEID_ServerDBX,
	DATABASEID_CoinShopDBX,
	DATABASEID_ShopCoinX,
	DATABASEID_BattleEvents,
};

enum EDatabaseDataTypeX
{
	PARAMTYPE_IntegerX,
	PARAMTYPE_StringX,
	PARAMTYPE_FloatX,
	PARAMTYPE_Int64X,
	PARAMTYPE_ShortX,
	PARAMTYPE_TimeX,
};

struct DatabaseStructureDataX
{
	EDatabaseIDX eDatabaseIDx;
	char* pszDatabaseName;
};


class Database
{
private:
	DatabaseStructureDataX* GetDatabaseData(EDatabaseIDX eDatabaseIDx);
	SQLHANDLE hEnv;
	SQLHANDLE hConnection;
	SQLHANDLE hStatement;
	EDatabaseIDX eID;
	char szDatabaseName[64];

	char szQuery[2048];

	CRITICAL_SECTION sCriticalSection;

public:

	bool Init(EDatabaseIDX eDatabaseIDx);

	BOOL SQLTimeStampToSystemTime(SYSTEMTIME* psSystemTime, SQL_TIMESTAMP_STRUCT* psSQLTimeStamp);

	BOOL Open();
	BOOL Prepare(const char* pszQuery);
	BOOL Execute(BOOL bFetch = TRUE);

	BOOL BindInputParameter(void* pParameter, int iPosition, EDatabaseDataTypeX eDataTypex);
	BOOL GetData(void* pParameter, int iSize, int iPosition, EDatabaseDataTypeX eDataTypex);
	BOOL NextRow();
	BOOL Close();

	static std::shared_ptr<Database> GetConnection(EDatabaseIDX eDatabaseIDx);

	Database();
	virtual ~Database();
};

