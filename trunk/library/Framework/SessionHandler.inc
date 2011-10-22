<?php
class Framework_SessionHandler
{
    private $_role_nm;
    private $_start_date;
    private $_user_id;
    private $_acl;

    private function __construct()
    {

    }

    public function setRole($role_nm)
    {
        $this->_role_nm = $role_nm;
    }

    public function getRole()
    {
        return $this->_role_nm;
    }
}