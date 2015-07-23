<?php

global $message;

$message = '';

session_start();

class Column
{
    /** @var string column name */
    private $name;

    /** @var string column typ */
    private $type;

    /**
     * Column constructor.
     * @param string $name
     * @param string $type
     */
    public function __construct($name, $type)
    {
        $this->name = $name;
        $this->type = $type;
    }

    /**
     * @return string
     */
    public function getName()
    {
        return $this->name;
    }

    /**
     * @return string
     */
    public function getType()
    {
        return $this->type;
    }



}

class ColumnFactory
{
    public function buildColumn($initData)
    {
        $column = new Column($initData['COLUMN_NAME'], $initData['DATA_TYPE']);
        return $column;
    }
}

function backWithMessage($inMessage)
{
    $message = $inMessage;
    require_once 'scanner.php';
    exit;
}

function cleanInputData($val)
{
    if (!isset($_POST[$val])) {
        return null;
    }
    return preg_replace('/[^A-Za-z0-9_\-]/', '', $_POST[$val]);
}

function getTables(PDO $connection)
{
    $tablesStatement = $connection->prepare("SHOW TABLES");
    $tablesStatement->execute();
    $tables = $tablesStatement->fetchAll();

    return array_map(
        function ($element) {
            return $element[0];
        },
        $tables
    );
}

function getColumns(PDO $connection, ColumnFactory $columnFactory,  $table)
{
    $statement = $connection->prepare("SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME=?");
    $statement->execute([$table]);
    $columns = $statement->fetchAll();

    return array_map(
        function($element) use($columnFactory) {
            return $columnFactory->buildColumn($element);
        },
        $columns
    );
}

function serializeTableConfig($objectName, $columns) {
    $attributeList = [];
    $typeList = [];

    foreach($columns as $column) {
        $attributeList[] = $column->getName();
        $typeList[] = $column->getType();
    }
    $_SESSION['objectName'] = $objectName;
    $_SESSION['attributeList'] = serialize($attributeList);
    $_SESSION['typeList'] = serialize($typeList);
    $_SESSION['classList'] = serialize([]);

}

if (!isset($_POST['send']) || $_POST['send'] !== "1") {
    backWithMessage('Please send request from scanner.php');
}

$host = cleanInputData('host');
$username = cleanInputData('username');
$password = cleanInputData('password');
$dbName = cleanInputData('db_name');
$tableName = cleanInputData('table_name');
$objectName = cleanInputData('object_name');

if (empty($host) || empty($username) || empty($password) || empty($dbName) || empty($tableName) || empty($objectName)) {
    backWithMessage('Please fill all required fields');
}

$pdoConnection = new PDO(sprintf("mysql:dbname=%s;host=%s", $dbName, $host), $username, $password);
$columnFactory = new ColumnFactory();


$tables = getTables($pdoConnection);
if (!in_array($tableName, $tables)) {
    backWithMessage(sprintf('Table %s not exists in %s', $tableName, $dbName));
}

$columns = getColumns($pdoConnection, $columnFactory, $tableName);

serializeTableConfig($objectName, $columns);

session_write_close();

header("Location: ../index.php");