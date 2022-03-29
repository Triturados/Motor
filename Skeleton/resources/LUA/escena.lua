function escenaEjemplo()
    IvanTontoTonto()
end


function scene0()
    scene:name("Escena de Dani")
    local obj = scene:createObject("Objeto de Dani")
    obj:addComponent("ComponenteDeContar")
end


function scene1()
    scene:name("Escena de Yojhan")
    local obj = scene:createObject("Objeto de Dani")
    obj:addComponent("FrameRate")
end