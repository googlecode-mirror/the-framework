<?php
/**
 * Response.inc
 *
 * This file contains the Framework_Response class.
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
 * This class is used to relay response parameters back to the bootstraping
 * process after the action is executed.
 *
 * @category Framework
 * @package  Framework
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version  Release: 1
 */
class Framework_Response
{
    const RESPONSE_TYPE_HTML = 0;
    const RESPONSE_TYPE_HTML_AJAX = 1;
    const RESPONSE_TYPE_JSON = 2;

    private $_response_type = Framework_Response::RESPONSE_TYPE_HTML;
    private $_json_response = null;

    private $has_error = false;
    private $error_message;
    
    /**
     * Returns the response type
     *
     * @access public
     * @return int
     */
    public function getResponseType()
    {
        return $this->_response_type;
    }

    /**
     * Set the response value and response type to JSON.
     *
     * @param mixed $obj the response value
     *
     * @access public
     * @return void
     */
    public function setJSONResponse($obj)
    {
        $this->_json_response = $obj;
        $this->_response_type = Framework_Response::RESPONSE_TYPE_JSON;
    }

    /**
     * Returns the json response value
     *
     * @access public
     * @return mixed
     */
    public function getJSONResponse()
    {
        return $this->_json_response;
    }

    /**
     * Is the response type JSON
     *
     * @access public
     * @return boolean
     */
    public function isJSONResponse()
    {
        return $this->_response_type === Framework_Response::RESPONSE_TYPE_JSON;
    }
    
    public function setErrorMessage($msg)
    {
        $this->has_error = true;
        $this->error_message = $msg;
    }
    
    public function getErrorMessage()
    {
        return $this->error_message;
    }
    
    public function hasError()
    {
        return $this->has_error;
    }
}