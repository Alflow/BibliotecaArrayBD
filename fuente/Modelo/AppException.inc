<?php

class AppException extends \Exception
{
    private array $errors;

    public function __construct(array $errors, string $message = "")
    {
        parent::__construct($message);
        $this->errors = $errors;
    }

    public function getErrors(): array
    {
        return $this->errors;
    }
}
