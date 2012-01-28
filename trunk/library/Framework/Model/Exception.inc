<?php
/**
* Exception.inc
*
* This file contains the Framework_Model_Exception class.
*
* PHP versions 4 and 5
*
* @category   Framework
* @package    Framework
* @subpackage Model
* @author     Tiago Seixas <tiagoafseixas@gmail.com>
* @license    GPLv3 http://www.gnu.org/licenses/gpl.html
* @version    SVN: 1
*/
/**
 * This class extends the Exception class from the PHP core. It should be used when
 * throwing exceptions at at the Model Layer of the application.
 *
 * @category   Framework
 * @package    Framework
 * @subpackage Model
 * @author     Tiago Seixas <tiagoafseixas@gmail.com>
 * @license    GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version    Release: 1
 * @abstract
 */
class Framework_Model_Exception extends Exception
{
    const EC_DB_CONNECTION_ERR = 0;
    const EC_DB_QUERY_ERR      = 1;
    
    private static $_ERR_MESSAGE = <<<ERR
Caught Framework_Model_Exception:
    Message   : %s
    Err. Code : %d
    Location  : %s @ %s
    Trace     :
%s
ERR;
    /**
     * returns a formated exception
     *
     * @access public
     * @returns string
     */
    public function __toString()
    {
        return sprintf(
            self::$_ERR_MESSAGE,
            $this->getMessage(), $this->getCode(),
            $this->getFile(), $this->getLine(),
            $this->getTraceAsString()
        );
    }
}