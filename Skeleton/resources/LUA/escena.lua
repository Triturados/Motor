function escenaEjemplo()
    IvanTontoTonto()
end


function scene0()
    scene:name("Escena de Dani")
    local obj = scene:createObject("Objeto de Dani")
    obj:addComponent("ComponenteDeContar"):sendMsg("Hola tontatatatata")
end


function scene1()
    scene:name("Escena de Daniel")
    local obj = scene:createObject("Objeto de Daniel")
    local comp = obj:addComponent("EscribirNumero")
    comp:send2(1, 0)
end