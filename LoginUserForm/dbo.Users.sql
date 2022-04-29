CREATE TABLE [dbo].[Users] (
    [Id]       INT           IDENTITY (1, 1) NOT NULL,
    [name]     VARCHAR (100) NOT NULL,
    [password] VARCHAR (MAX) NOT NULL,
    [secretQ] VARCHAR(MAX) NOT NULL, 
    [secretA] VARCHAR(MAX) NOT NULL, 
    PRIMARY KEY CLUSTERED ([Id] ASC)
);

