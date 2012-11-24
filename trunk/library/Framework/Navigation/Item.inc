<?php
/**
 * Item.inc
 *
 * This file contains the Framework_Navigation_Item class.
 *
 * PHP versions 4 and 5
 *
 * @category   Framework
 * @package    Framework
 * @subpackage Navigation
 * @author     Tiago Seixas <tiagoafseixas@gmail.com>
 * @license    GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version    SVN: 1
 */
/**
 * This class represents an item in the navigation.
 *
 * @category   Framework
 * @package    Framework
 * @subpackage Navigation
 * @author     Tiago Seixas <tiagoafseixas@gmail.com>
 * @license    GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version    Release: 1
 */
class Framework_Navigation_Item
{
    private $_id;
    private $_controller;
    private $_action;
    private $_label;
    private $_auth;
    private $_link;
    private $_nav_path;

    private $_children;

    /**
     * The constructor for the Item class.
     *
     * @param array $item array that contains the item parameters.
     */
    public function __construct($item)
    {
        $this->_id = $item['id'];
        $this->_link = "/{$item['nav_path'][0]}";
        if (sizeof($item['nav_path']) > 1) {
            $this->_link .= "/" . $item['nav_path'][1];
        }

        $this->_label = $item['label'];
        $this->_auth = $item['auth'];
        $this->_controller = $item['controller'];
        $this->_action = $item['action'];
        $this->_nav_path = $item['nav_path'];
        $this->_children = array();
    }

    /**
     * Returns a string containing the link
     *
     * @return string
     */
    public function getLink()
    {
        return $this->_link;
    }

    /**
     * Returns a string containing the label
     *
     * @return string
     */
    public function getLabel()
    {
        return utf8_decode(gettext($this->_label));
    }

    /**
     * Returns the auth parameter in the navigation xml
     *
     * @return string
     */
    public function getAuth()
    {
        return $this->_auth;
    }

    /**
     * Returns the name of the controller.
     *
     * @return string
     */
    public function getController()
    {
        return $this->_controller;
    }

    /**
     * Returns the name of the action.
     *
     * @return string
     */
    public function getAction()
    {
        return $this->_action;
    }

    /**
     * Receives the current controller and action and checks against its own.
     *
     * @param string $cur_controller The current controller
     * @param string $cur_action     The current action
     *
     * @return bool
     */
    public function isSelected($cur_controller, $cur_action)
    {
        if (sizeof($this->_nav_path) == 1) {
            return $cur_controller === $this->_nav_path[0];
        } else {
            return $cur_controller === $this->_nav_path[0]
            && $cur_action === $this->_nav_path[1];
        }
    }

    public function addChild($item)
    {
        $this->_children[] = $item;
    }

    public function getChildren()
    {
        return $this->_children;
    }

    public function getId()
    {
        return $this->_id;
    }
}
