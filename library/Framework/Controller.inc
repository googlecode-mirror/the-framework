<?php
/**
 * Controller.inc
 *
 * This file contains the Framework_Controller class.
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
 * This class is the base for every controller in the application.
 *
 * @category Framework
 * @package  Framework
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version  Release: 1
 * @abstract
 */
abstract class Framework_Controller
{
    /**
     * 
     * @var Framework_Request
     */
    protected $request;
    
    /**
     * 
     * @var Framework_Response
     */
    protected $response;
    
    /**
     * 
     * @var Log
     */
    protected $logger;

    /**
     * 
     * @var Smarty
     */
    protected $view;

    /**
     * Constructor for the Framework_Controller class.
     *
     * @param Framework_Request  $request  the Request object
     * @param Framework_Response $response the Response object
     * @param Smarty             $view     the View Object
     *
     * @access public
     * @return Framework_Controller
     */
    public function __construct($request = null, $response = null, $view=null)
    {
        $this->request = $request;
        $this->response = $response;
        $this->view = $view;
    }

    /**
     * Initialization function.
     *
     * @access public
     * @abstract
     * @return void
     */
    abstract function init();

    /**
     * Returns the Request object
     *
     * @access public
     * @return Framework_Request
     */
    public function getRequest()
    {
        return $this->request;
    }

    /**
     * Returns the Response object
     *
     * @access public
     * @return Framework_Response
     */
    public function getResponse()
    {
        return $this->response;
    }

    /**
     * Returns the View object
     *
     * @access public
     * @return Smarty
     */
    public function getView()
    {
        return $this->view;
    }

    /**
     * Redirects the request. Exists on completion.
     *
     * @param string $controller the name of the controller
     * @param string $action     the name of the action
     *
     * @access public
     * @return void
     */
    public function redirect($controller, $action)
    {
        header("Location:/{$controller}/{$action}");
        session_write_close();
        exit;
    }
}