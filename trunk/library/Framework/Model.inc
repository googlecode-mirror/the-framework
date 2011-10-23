<?php
/**
 * Model.inc
 *
 * This file contains the Framework_Model class.
 *
 * PHP versions 4 and 5
 *
 * @category Framework
 * @package  Framework
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version  SVN: 1
 */
/**
 * This class is the base for every model in the application.
 *
 * @category Framework
 * @package  Framework
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version  Release: 1
 * @abstract
 */
abstract class Framework_Model
{
    /**
     * The database connection holder.
     *
     * @access protected
     * @var PDO
     */
    protected static $dbh;
    
    protected $logger;
    
    /**
     * Connects to the database.
     *
     * @access protected
     * @uses Framework_ConnectionFactory
     * @return void
     */
    protected function connect()
    {
        $pdo_config = Framework_Registry::get('db_configs');
        $dsn = $pdo_config['pdo_driver'] .
            ':host=' .
            $pdo_config['mysql_host'] .
            ';dbname=' .
            $pdo_config['mysql_dbname'];
                 
        try{
            self::$dbh = new PDO(
                $dsn,
                $pdo_config['mysql_user'],
                $pdo_config['mysql_password']
            );
            self::$dbh->setAttribute(
                PDO::ATTR_ERRMODE,
                PDO::ERRMODE_EXCEPTION
            );
        } catch (PDOException $e) {
            print "Error!: " . $e->getMessage() . "<br/>";
            die();
        }
    }
    
    /**
     * Executes an insert statement
     *
     * @param string $query  the query to be executed
     * @param array  $params a list of parameters
     *
     * @uses PDO
     * @uses Log
     *
     * @return string the last iserted id
     */
    protected function executeDefaultInsert($query, $params)
    {
        try {
            if (false === self::$dbh instanceof PDO) {
                $this->connect();
            }
            $stmt = self::$dbh->prepare($query);
            $stmt->execute($params);
        } catch (PDOException $e) {
            $this->logger->err($e->getMessage());
            write_error_msg("Model", $e);
            return false;
        }

        return self::$dbh->lastInsertId();
    }
    /**
     * Executes a select on the database
     *
     * @param string $query  the query to be executed
     * @param array  $params a list of parameters
     *
     * @uses PDO
     * @uses Log
     *
     * @return array
     */
    protected function executeDefaultSelect($query, $params = null)
    {
        $ret = null;

        try {
            if (false === self::$dbh instanceof PDO) {
                $this->connect();
            }

            $stmt = self::$dbh->prepare($query);
            
            if ($params !== null) {
                $stmt->execute($params);
            } else {
                $stmt->execute();
            }
            
            $ret = $stmt->fetchAll(PDO::FETCH_ASSOC);
        } catch(PDOException $e) {
            $this->logger->err($e->getMessage());
            write_error_msg("Model", $e);
        }
        return $ret;
    }
    
    /**
     * Executes an update on the database
     *
     * @param string $query  the query to be executed
     * @param array  $params a list of parameters
     *
     * @uses PDO
     * @uses Log
     *
     * @return boolean
     */
    protected function executeDefaultUptade($query, $params)
    {
        $result = false;
        try {
            if (false === self::$dbh instanceof PDO) {
                $this->connect();
            }
            $stmt = self::$dbh->prepare($query);
            $stmt->execute($params);
            $result = $stmt->rowCount() > 0 ? true : false;
        } catch (PDOException $e) {
            $this->logger->err($e->getMessage());
            write_error_msg("Model", $e);
        }
        return $result;
    }

    /**
     * Executes a select query and stores the value in the APC.
     *
     * @param string $query   the query statement
     * @param array  $params  an array of parameters to use in the query
     * @param long   $timeout the ammount of time the query will be stored
     *
     * @access protected
     * @return resultset
     */
    protected function selectWithCache($query, $params = array(), $timeout = 43200)
    {
        $apc_key = md5($query . join("", $params));
        
        if (false === apc_fetch($apc_key)) {
            try {
                if (false === self::$dbh instanceof PDO) {
                    $this->connect();
                }
                
                $stmt = self::$dbh->prepare($query);
                
                if ($params !== null) {
                    $stmt->execute($params);
                } else {
                    $stmt->execute();
                }
                
                $ret = $stmt->fetchAll(PDO::FETCH_ASSOC);

                apc_add($apc_key, $ret, $timeout);
                write_info_msg("Model", "Added $apc_key to APC.");
            } catch(PDOException $e) {
                $this->logger->err($e->getMessage());
                write_error_msg("Model", $e);
            }
        } else {
            write_info_msg("Model", "Fetched $apc_key from APC.");
            $ret = apc_fetch($apc_key);
        }

        return $ret;
    }
}